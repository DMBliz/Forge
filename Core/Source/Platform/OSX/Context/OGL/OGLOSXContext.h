#pragma once

#if defined(__APPLE__)
#  include <TargetConditionals.h>
#endif


#if defined(__OBJC__)
#  import <CoreVideo/CoreVideo.h>
#  import <AppKit/AppKit.h>
#import <atomic>

typedef NSOpenGLContext* NSOpenGLContextPtr;
typedef NSOpenGLPixelFormat* NSOpenGLPixelFormatPtr;
#else
#  include <objc/objc.h>
typedef void* CVDisplayLinkRef;
typedef id NSOpenGLContextPtr;
typedef id NSOpenGLPixelFormatPtr;
#endif

#include "Platform/Api/Context.h"

@class OGLView;
@class OSXView;

namespace Forge
{

    class OGLOSXContext : public Context
    {
    public:
        void CreateContext(Window &win, unsigned int sampleCount) override;

        void DeleteContext() override;

        void setActive() override;

        void PlatformUpdate() override;
        void RenderCallback();
    private:
        OSXView* openGLView;
        NSOpenGLContextPtr openGLContext = nil;
        NSOpenGLPixelFormatPtr pixelFormat = nil;

        CVDisplayLinkRef displayLink = nullptr;

        std::atomic_bool running{false};
    };

}