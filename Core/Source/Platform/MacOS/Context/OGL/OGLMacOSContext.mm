#import <Platform/OSX/MacOSView.h>
#include "Platform/OSX/MacOSWindow.h"
#include "OGLMacOSContext.h"
#include "OGLView.h"
#import "OGLView.h"

static CVReturn renderCallback(CVDisplayLinkRef,
                               const CVTimeStamp*,
                               const CVTimeStamp*,
                               CVOptionFlags,
                               CVOptionFlags*,
                               void* userInfo)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    try
    {
        Forge::OGLMacOSContext* renderDevice = static_cast<Forge::OGLMacOSContext*>(userInfo);
        renderDevice->RenderCallback();
    }
    catch (const std::exception& e)
    {
        return kCVReturnError;
    }

    [pool release];

    return kCVReturnSuccess;
}

namespace Forge
{

    void OGLMacOSContext::CreateContext(Window &win, unsigned int sampleCount)
    {
        MacOSWindow& window = static_cast<MacOSWindow&>(win);

        for (NSOpenGLPixelFormatAttribute openGLVersion : {NSOpenGLProfileVersion4_1Core, NSOpenGLProfileVersion3_2Core, NSOpenGLProfileVersionLegacy})
        {
            // Create pixel format
            std::vector<NSOpenGLPixelFormatAttribute> attributes =
                    {
                            NSOpenGLPFAAccelerated,
                            NSOpenGLPFANoRecovery,
                            NSOpenGLPFADoubleBuffer,
                            NSOpenGLPFAOpenGLProfile, openGLVersion,
                            NSOpenGLPFAColorSize, 24,
                            NSOpenGLPFAAlphaSize, 8,
                            NSOpenGLPFADepthSize, static_cast<NSOpenGLPixelFormatAttribute>(24),
                            NSOpenGLPFAStencilSize, static_cast<NSOpenGLPixelFormatAttribute>(8)
                    };

            if (sampleCount)
            {
                attributes.push_back(NSOpenGLPFAMultisample);
                attributes.push_back(NSOpenGLPFASampleBuffers);
                attributes.push_back(1);
                attributes.push_back(NSOpenGLPFASamples);
                attributes.push_back(sampleCount);
            }

            attributes.push_back(0);

            pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes.data()];


            if (pixelFormat)
            {
                switch (openGLVersion)
                {
                    case NSOpenGLProfileVersionLegacy:
                        LOG_INFO("OpenGL 2 pixel format created");
                        break;
                    case NSOpenGLProfileVersion3_2Core:
                        LOG_INFO("OpenGL 3.2 pixel format created");
                        break;
                    case NSOpenGLProfileVersion4_1Core:
                        LOG_INFO("OpenGL 4.1 pixel format created");
                        break;
                }
                break;
            }
        }

        if (!pixelFormat)
            throw std::runtime_error("Failed to crete OpenGL pixel format");

        // Create OpenGL context
        openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        [openGLContext makeCurrentContext];

        openGLView = [[OGLView alloc] initWithWindow:&window];

        [openGLView setWantsBestResolutionOpenGLSurface:window.isHighDpi()];

        [openGLView setAcceptsTouchEvents:YES];
        [openGLView setWantsRestingTouches:YES];

        [openGLView setOpenGLContext:openGLContext];

        window.setContentView(openGLView);

        [openGLContext setView:openGLView];

        GLint swapInt = 1;
        [openGLContext setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];

        CGDirectDisplayID displayId = window.getDisplayID();

        if (CVDisplayLinkCreateWithCGDisplay(displayId, &displayLink) != kCVReturnSuccess)
            throw std::runtime_error("Failed to create display link");

        if (CVDisplayLinkSetOutputCallback(displayLink, ::renderCallback, this) != kCVReturnSuccess)
            throw std::runtime_error("Failed to set output callback for the display link");

        running = true;

        if (CVDisplayLinkStart(displayLink) != kCVReturnSuccess)
            throw std::runtime_error("Failed to start display link");
    }

    void OGLMacOSContext::DeleteContext()
    {
        
    }

    void OGLMacOSContext::PlatformUpdate()
    {
        [openGLContext flushBuffer];
    }

    void OGLMacOSContext::RenderCallback()
    {
        if ([NSOpenGLContext currentContext] != openGLContext)
            [openGLContext makeCurrentContext];
    }

    void OGLMacOSContext::setActive()
    {
        [openGLContext makeCurrentContext];
    }
}