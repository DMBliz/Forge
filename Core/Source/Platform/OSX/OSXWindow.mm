//
// Created by Дмитрий Метелица on 2019-07-01.
//

//#include "Platform/OSX/Context/OGL/OGLView.h"
#import <Platform/OSX/Context/OGL/OGLView.h>
#import <AppKit/AppKit.h>
#import "Cocoa/Cocoa.h"
#include "OSXWindow.h"


@interface WindowDelegate: NSObject<NSWindowDelegate>
@end


@implementation WindowDelegate
{
    Forge::OSXWindow* window;
}

-(id)initWithWindow:(Forge::OSXWindow*)initWindow
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
    window->handleMinituarize();
}

- (void)windowDidDeminiaturize:(__unused NSNotification*)notification
{
    window->handleDeminituarize();
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


@interface AppDelegate: NSObject<NSApplicationDelegate>
@end

@implementation AppDelegate
{
    Forge::OSXWindow* application;
}

-(id)InitApplication:(Forge::OSXWindow*)initApplication
{
    if(self == [super init])
        application = initApplication;

    return self;
}

-(void)applicationWillFinishLaunching:(__unused NSNotification*)notification
{
    //init
}

-(void)applicationDidFinishLaunching:(__unused NSNotification*)notification
{
    //start
    [NSApp stop:nil];
    
    @autoreleasepool {

    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
    [NSApp postEvent:event atStart:YES];

    } // autoreleasepool
}

-(void)applicationWillTerminate:(__unused NSNotification*)notification
{
    //terminate
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(__unused NSApplication*)sender
{
    return YES;
}

-(BOOL)application:(__unused NSApplication*)sender openFile:(NSString*)filename
{
    return false;
}

-(void)applicationDidBecomeActive:(__unused NSNotification*)notification
{

}

-(void)applicationDidResignActive:(__unused NSNotification*)notification
{

}

-(void)handleQuit:(__unused id)sender
{
    [[NSApplication sharedApplication] terminate:nil];
}
@end

namespace Forge
{
    OSXWindow::OSXWindow()
    {
        pool = [[NSAutoreleasePool alloc] init];

        application = [NSApplication sharedApplication];
        [application activateIgnoringOtherApps:YES];
        [application setDelegate:[[[AppDelegate alloc] init] autorelease]];
        application.activationPolicy = NSApplicationActivationPolicyRegular;

        NSMenu* mainMenu = [[[NSMenu alloc] initWithTitle:@"Main Menu"] autorelease];

        NSMenuItem* mainMenuItem = [[[NSMenuItem alloc] init] autorelease];
        [mainMenu addItem:mainMenuItem];

        NSMenu* subMenu = [[[NSMenu alloc] init] autorelease];
        [mainMenuItem setSubmenu:subMenu];

        NSMenuItem* quitItem = [[[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(handleQuit:) keyEquivalent:@"q"] autorelease];
        [quitItem setTarget:[application delegate]];
        [subMenu addItem:quitItem];

        application.mainMenu = mainMenu;
    }

    OSXWindow::~OSXWindow()
    {
        if(pool)
            [pool release];
    }

    void OSXWindow::create(const WindowCreationDesc& creationDesc)
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

        NSRect frame = NSMakeRect(round(screen.frame.size.width / 2.0F - windowSize.width / 2.0F),
                                  round(screen.frame.size.height / 2.0F - windowSize.height / 2.0F),
                                  windowSize.width, windowSize.height);

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

        [window setCollectionBehavior:windowState == WindowState::FULLSCREEN ? NSWindowCollectionBehaviorFullScreenAuxiliary
                                                                             : NSWindowCollectionBehaviorFullScreenPrimary];

        if (windowState == WindowState::FULLSCREEN)
        {
            if (CGDisplayCapture(displayId) != kCGErrorSuccess)
                throw std::runtime_error("Failed to capture the main display");

            nativeWindowRect = frame;
            [window setStyleMask:NSBorderlessWindowMask];

            NSRect screenRect = [screen frame];
            [window setFrame:screenRect display:YES animate:NO];

            CGWindowLevel windowLevel = CGShieldingWindowLevel();
            [window setLevel:windowLevel];
        }
        else if (windowState == WindowState::MAXIMIZED)
            [window toggleFullScreen:nil];

        [window setTitle:static_cast<NSString *_Nonnull>([NSString stringWithUTF8String:windowTitle.CString()])];

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

        this->windowRect.width = static_cast<uint32_t>(windowSize.width);
        this->windowRect.height = static_cast<uint32_t>(windowSize.height);

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

        [application run];
    }

    void OSXWindow::close()
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

    void OSXWindow::platformUpdate()
    {
        @autoreleasepool {

            for (;;)
            {
                NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                    untilDate:[NSDate distantPast]
                                                       inMode:NSDefaultRunLoopMode
                                                      dequeue:YES];
                if (event == nil)
                    break;

                [NSApp sendEvent:event];
            }

        }
    }

    void OSXWindow::setClipboard(const String &data)
    {

    }

    const String& OSXWindow::getClipboard()
    {
        return String();
    }

    void OSXWindow::setCursorPosition(const Vector2i &newPos)
    {

    }

    void OSXWindow::handleResignKeyChange()
    {

    }

    void OSXWindow::handleBecomeKeyChange()
    {

    }

    void OSXWindow::handleScreenChange()
    {

    }

    void OSXWindow::handleScaleFactorChange()
    {

    }

    void OSXWindow::handleFullscreenChange(bool fullscreen)
    {

    }

    void OSXWindow::handleDeminituarize()
    {

    }

    void OSXWindow::handleMinituarize()
    {

    }

    void OSXWindow::handleClose()
    {

    }

    void OSXWindow::handleResize()
    {

    }

    NSViewPtr OSXWindow::getNativeView() const
    {
        return view;
    }

    CGDirectDisplayID OSXWindow::getDisplayID() const
    {
        return displayId;
    }

    void OSXWindow::bringToFront()
    {
        [window orderFront:nil];
    }

    void OSXWindow::show()
    {
        [window orderFront:nil];
    }

    void OSXWindow::hide()
    {
        [window orderOut:nil];
    }

    const NSRect& OSXWindow::getWindowFrame() const
    {
        return windowFrame;
    }

    void OSXWindow::setContentView(NSView* view)
    {
        this->view = view;
        window.contentView = view;
    }

    NSView* OSXWindow::getContentView() const
    {
        return view;
    }

    void OSXWindow::setWindowState(WindowState windowState)
    {
        if(windowState == this->windowState)
            return;

        switch(windowState)
        {
            case WindowState::FULLSCREEN:
                break;
            case WindowState::MAXIMIZED:
                nativeWindowRect = [screen visibleFrame];
                [window setFrame:nativeWindowRect display:YES];
                break;
            case WindowState::WINDOWED:
                break;
        }
        Window::setWindowState(windowState);
    }

    void OSXWindow::setMinimized(bool value)
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

    Input* OSXWindow::getInput()
    {
        return &input;
    }
}
