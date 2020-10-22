//
// Created by Dmitry Metelitsa on 2019-07-01.
//

//#include "Platform/MacOS/Context/OGL/OGLView.h"
#import "Platform/MacOS/Context/OGL/OGLView.h"
#import <AppKit/AppKit.h>
#import "Cocoa/Cocoa.h"
#import "MacOSView.h"
#include "MacOSWindow.h"
#import "MacOSCursor.h"


@interface WindowDelegate: NSObject<NSWindowDelegate>
@end


@implementation WindowDelegate
{
    Forge::MacOSWindow* window;
}

-(id)initWithWindow:(Forge::MacOSWindow*)initWindow
{
    if(self = [super init])
        window = initWindow;

    return self;
}

-(void)windowDidResize:(__unused NSNotification*)notification
{
    window->handleResize();
}

-(void)windowWillClose:(__unused NSNotification*)notification
{
    window->handleClose();
}

-(void)windowDidMiniaturize:(NSNotification *)notification
{
    window->handleMiniaturize();
}

- (void)windowDidDeminiaturize:(__unused NSNotification*)notification
{
    window->handleDeminiaturize();
}

-(void)windowDidEnterFullScreen:(__unused NSNotification*)notification
{
    window->handleFullscreenChange(true);
}

-(void)windowDidExitFullScreen:(__unused NSNotification*)notification
{
    window->handleFullscreenChange(false);
}

-(void)windowDidChangeBackingProperties:(__unused NSNotification*)notification
{
    window->handleScaleFactorChange();
}

-(void)windowDidChangeScreen:(__unused NSNotification*)notification
{
    window->handleScreenChange();
}

-(void)windowDidBecomeKey:(__unused NSNotification*)notification
{
    window->handleBecomeKeyChange();
}

-(void)windowDidResignKey:(__unused NSNotification*)notification
{
    window->handleResignKeyChange();
}
@end


namespace Forge
{
    MacOSWindow::MacOSWindow()
    {
    }

    MacOSWindow::~MacOSWindow()
    {
    }

    void MacOSWindow::create(const WindowCreationDesc& creationDesc)
    {
        windowTitle = creationDesc.title;
        windowRect = creationDesc.size;
        windowState = creationDesc.openState;
        resizable = creationDesc.resizable;
        highDPI = creationDesc.highDPI;

        screen = [NSScreen mainScreen];
        displayId = [[[screen deviceDescription] objectForKey:@"NSScreenNumber"] unsignedIntValue];

        CGSize windowSize;

        if (highDPI)
        {
            windowSize.width = this->windowRect.width;
            windowSize.height = this->windowRect.height;
        }
        else
        {
            windowSize.width = round(this->windowRect.width / screen.backingScaleFactor);
            windowSize.height = round(this->windowRect.height / screen.backingScaleFactor);
        }

        if (windowSize.width <= 0.0F)
            windowSize.width = round(screen.frame.size.width * 0.8);
        if (windowSize.height <= 0.0F)
            windowSize.height = round(screen.frame.size.height * 0.8);

        NSRect frame = NSMakeRect(windowRect.x, windowRect.y, windowSize.width, windowSize.height);

        windowStyleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

        if (resizable)
            windowStyleMask |= NSResizableWindowMask;

        window = [[NSWindow alloc] initWithContentRect:frame
                                             styleMask:static_cast<NSWindowStyleMask>(windowStyleMask)
                                               backing:NSBackingStoreBuffered
                                                 defer:NO
                                                screen:screen];
        [window setReleasedWhenClosed:NO];

        window.acceptsMouseMovedEvents = YES;
        windowDelegate = [[WindowDelegate alloc] initWithWindow:this];
        window.delegate = windowDelegate;

        [window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];

        this->windowRect.width = static_cast<uint32_t>(windowSize.width);
        this->windowRect.height = static_cast<uint32_t>(windowSize.height);

        if (windowState == WindowState::FULLSCREEN_BORDERLESS)
        {
            if (CGDisplayCapture(displayId) != kCGErrorSuccess)
                throw std::runtime_error("Failed to capture the main display");

            windowFrame = frame;
            [window setStyleMask:NSBorderlessWindowMask];

            NSRect screenRect = [screen frame];
            [window setFrame:screenRect display:YES animate:NO];

            CGWindowLevel windowLevel = CGShieldingWindowLevel();
            [window setLevel:windowLevel];

            windowRect.set(0, 0, static_cast<int>(screen.frame.size.width),
                           static_cast<int>(screen.frame.size.height));
        }
        else if (windowState == WindowState::FULLSCREEN)
        {
            [window setFrame:[screen frame] display:YES animate:YES];
            [window toggleFullScreen:nil];

            windowRect.set(static_cast<int>(screen.frame.origin.x), static_cast<int>(screen.frame.origin.x),
                           static_cast<int>(screen.frame.size.width), static_cast<int>(screen.frame.size.height));
        }
        else if (windowState == WindowState::MAXIMIZED)
        {
            [window setFrame:screen.visibleFrame display:YES];
            windowRect.set(static_cast<int>(screen.visibleFrame.origin.x),
                           static_cast<int>(screen.visibleFrame.origin.y),
                           static_cast<int>(screen.visibleFrame.size.width),
                           static_cast<int>(screen.visibleFrame.size.height));
        }

        [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.cString()])];

        if ([NSWindow respondsToSelector:@selector(setAllowsAutomaticWindowTabbing:)])
        {
            BOOL value = NO;

            NSMethodSignature *signature = [NSWindow methodSignatureForSelector:@selector(setAllowsAutomaticWindowTabbing:)];
            NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];
            [invocation setSelector:@selector(setAllowsAutomaticWindowTabbing:)];
            [invocation setArgument:&value atIndex:2];
            [invocation invoke];
        }

        windowFrame = [NSWindow contentRectForFrameRect:[window frame]
                                              styleMask:[window styleMask]];

        window.contentView = view;

        [window makeKeyAndOrderFront:nil];

        if (highDPI)
        {
            contentScale = static_cast<float>(screen.backingScaleFactor);
            resolution = Vector2i(this->windowRect.width * static_cast<int32>(contentScale),
                                  this->windowRect.height * static_cast<int32>(contentScale));
        }
        else
        {
            contentScale = 1.0F;
            resolution = this->windowRect.size();
        }
    }

    void MacOSWindow::close()
    {
        if (view)
        {
            [view release];
            view = nil;
        }

        if (window)
        {
            window.delegate = nil;
            [window close];
            [window release];
            window = nil;
        }

        if (windowDelegate)
        {
            [windowDelegate release];
            windowDelegate = nil;
        }
    }

    void MacOSWindow::platformUpdate()
    {
        [view beginUpdate];
        onWindowEventsFinished();
        if (context != nullptr)
            context->platformUpdate();
    }

    void MacOSWindow::handleResignKeyChange()
    {
        onActiveStateChanged.Invoke(this, false);
    }

    void MacOSWindow::handleBecomeKeyChange()
    {
        onActiveStateChanged.Invoke(this, true);
    }

    void MacOSWindow::handleScreenChange()
    {
        onScreenChange.Invoke(this);
    }

    void MacOSWindow::handleScaleFactorChange()
    {
        contentScale = static_cast<float>(window.backingScaleFactor);
        resolution = windowRect.size() * contentScale;

        onResolutionChanged.Invoke(this, resolution);
    }

    void MacOSWindow::handleFullscreenChange(bool fullscreen)
    {
        resetWindowState();
        this->fullscreen = fullscreen;
    }

    void MacOSWindow::handleDeminiaturize()
    {
        minimized = false;
        onMinimizeChanged(this, false);
    }

    void MacOSWindow::handleMiniaturize()
    {
        minimized = true;
        onMinimizeChanged(this, true);
    }

    void MacOSWindow::handleClose()
    {
        onWindowClose.Invoke(this);
    }

    void MacOSWindow::handleResize()
    {
        NSRect frame = [NSWindow contentRectForFrameRect:window.frame
                                               styleMask:window.styleMask];

        windowRect.set(static_cast<int>(frame.origin.x), static_cast<int>(frame.origin.y),
                       static_cast<int>(frame.size.width),
                       static_cast<int>(frame.size.height));
        resolution = windowRect.size() * contentScale;

        onWindowSizeChanged.Invoke(this, windowRect);
        onResolutionChanged.Invoke(this, resolution);
    }

    NSViewPtr MacOSWindow::getNativeView() const
    {
        return view;
    }

    CGDirectDisplayID MacOSWindow::getDisplayID() const
    {
        return displayId;
    }

    void MacOSWindow::bringToFront()
    {
        [window orderFront:nil];
    }

    void MacOSWindow::show()
    {
        [window orderFront:nil];
    }

    void MacOSWindow::hide()
    {
        [window orderOut:nil];
    }

    const NSRect& MacOSWindow::getWindowFrame() const
    {
        return windowFrame;
    }

    void MacOSWindow::setContentView(MacOSView* view)
    {
        this->view = view;
        [window setContentView:view];
        [window makeFirstResponder:view];
    }

    NSView* MacOSWindow::getContentView() const
    {
        return view;
    }

    void MacOSWindow::setWindowState(WindowState windowState)
    {
        if(windowState == this->windowState)
            return;

        if(this->windowState == WindowState::FULLSCREEN)
            [window toggleFullScreen:nil];

        if(borderlessFullscreen && windowState != WindowState::FULLSCREEN_BORDERLESS)
            borderlessFullscreen = false;

        switch(windowState)
        {
            case WindowState::FULLSCREEN:
            {
                [window setStyleMask:static_cast<NSWindowStyleMask>(windowStyleMask)];
                [window setFrame:[screen frame] display:YES animate:YES];
                [window toggleFullScreen:nil];
                [window setLevel:NSNormalWindowLevel];
                [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.cString()])];

                windowRect.set(static_cast<int>(screen.frame.origin.x), static_cast<int>(screen.frame.origin.x),
                               static_cast<int>(screen.frame.size.width), static_cast<int>(screen.frame.size.height));
                resolution = windowRect.size() * contentScale;
                break;
            }
            case WindowState::MAXIMIZED:
            {
                [window setStyleMask:static_cast<NSWindowStyleMask>(windowStyleMask)];
                [window setFrame:screen.visibleFrame display:YES animate:YES];
                [window setLevel:NSNormalWindowLevel];
                [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.cString()])];


                windowRect.set(static_cast<int>(screen.visibleFrame.origin.x),
                               static_cast<int>(screen.visibleFrame.origin.y),
                               static_cast<int>(screen.visibleFrame.size.width),
                               static_cast<int>(screen.visibleFrame.size.height));
                resolution = windowRect.size() * contentScale;
                break;
            }
            case WindowState::WINDOWED:
            {
                [window setStyleMask:static_cast<NSWindowStyleMask>(windowStyleMask)];
                [window setFrame:windowFrame display:YES animate:YES];
                [window setLevel:NSNormalWindowLevel];
                [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.cString()])];

                windowRect.set(static_cast<int>(windowFrame.origin.x), static_cast<int>(windowFrame.origin.y),
                               static_cast<int>(windowFrame.size.width), static_cast<int>(windowFrame.size.height));
                resolution = windowRect.size() * contentScale;
                break;
            }
            case WindowState::FULLSCREEN_BORDERLESS:
            {
                [window setStyleMask:NSBorderlessWindowMask];
                [window setFrame:[screen frame] display:YES animate:YES];
                [window setLevel:CGShieldingWindowLevel()];

                resetWindowState();
                borderlessFullscreen = true;

                windowRect.set(static_cast<int>(screen.frame.origin.x), static_cast<int>(screen.frame.origin.x),
                               static_cast<int>(screen.frame.size.width), static_cast<int>(screen.frame.size.height));
                resolution = windowRect.size() * contentScale;
                break;
            }
        }
        [window makeFirstResponder:view];
    }

    void MacOSWindow::setMinimized(bool value)
    {
        if(value == minimized)
            return;
        if(value)
        {
            [window miniaturize:nil];
        }
        else
        {
            [window deminiaturize:nil];
        }
        Window::setMinimized(value);
    }

    InputManager* MacOSWindow::getInput()
    {
        return &input;
    }

    void MacOSWindow::resetWindowState()
    {
        windowed = false;
        fullscreen = false;
        borderlessFullscreen = false;
        maximized = false;
    }

    void MacOSWindow::onWindowEventsFinished()
    {
        maximized = window.frame.origin.x <= screen.visibleFrame.origin.x &&
                    window.frame.origin.y <= screen.visibleFrame.origin.y &&
                    window.frame.size.width >= screen.visibleFrame.size.width &&
                    window.frame.size.height >= screen.visibleFrame.size.height && !fullscreen && !borderlessFullscreen;

        windowed = !maximized && !fullscreen && !borderlessFullscreen;

        WindowState newState = windowState;

        if(windowed)
            newState = WindowState::WINDOWED;
        else if(maximized)
            newState = WindowState::MAXIMIZED;
        else if(fullscreen)
            newState = WindowState::FULLSCREEN;
        else if(borderlessFullscreen)
            newState = WindowState::FULLSCREEN_BORDERLESS;

        if(newState != windowState)
        {
            windowState = newState;
            onWindowStateChanged.Invoke(this, windowState);
        }
    }

    void MacOSWindow::setCursor(Cursor* cursor)
    {
        Window::setCursor(cursor);
        if(cursor == nullptr)
        {
            [NSCursor hide];
            return;
        }
        MacOSCursor* cur = static_cast<MacOSCursor*>(cursor);
        NSCursorPtr nativeCursor = cur->getNativeCursor();
        [nativeCursor set];
    }

    void MacOSWindow::setTitle(const String& newTitle)
    {
        Window::setTitle(newTitle);

        [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.cString()])];
    }

    void MacOSWindow::setWindowRect(const RectI& newSize)
    {
        Window::setWindowRect(newSize);
    }

    void MacOSWindow::setContext(Context* context)
    {
        Window::setContext(context);

        context->init(*this, 1);
    }
}
