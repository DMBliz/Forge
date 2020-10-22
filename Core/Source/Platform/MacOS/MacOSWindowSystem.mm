//
// Created by Dmitry Metelitsa on 2019-11-23.
//

#import <AppKit/AppKit.h>
#include "MacOSWindowSystem.h"
#include "MacOSWindow.h"
#include "MacOSCursor.h"


@interface AppDelegate: NSObject<NSApplicationDelegate>
@end

@implementation AppDelegate
{
    Forge::MacOSWindow* application;
}

-(id)InitApplication:(Forge::MacOSWindow*)initApplication
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
    LOG_INFO("application active");
}

-(void)applicationDidResignActive:(__unused NSNotification*)notification
{
    LOG_INFO("application inactive");
}

-(void)handleQuit:(__unused id)sender
{
    [[NSApplication sharedApplication] terminate:nil];
}
@end


namespace Forge
{

    void MacOSWindowSystem::init()
    {
        if (isInitialized)
            return;
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

        [application run];
        isInitialized = true;
    }

    void MacOSWindowSystem::update()
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

        for (auto& window : windows)
        {
            window.second->platformUpdate();
        }
    }

    Window* MacOSWindowSystem::createWindow(const WindowCreationDesc& desc)
    {
        MacOSWindow* window;
        window = new MacOSWindow();
        window->create(desc);
        if (!desc.title.isEmpty())
        {
            windows[desc.title.hash()] = window;
        }
        else
        {
            windows[lastID++] = window;
        }
        return window;
    }

    MacOSWindowSystem::~MacOSWindowSystem()
    {
        if(pool)
            [pool release];
    }

    Cursor* MacOSWindowSystem::createCursor(SystemCursor cursorType)
    {
        return new MacOSCursor(cursorType);
    }

    Cursor* MacOSWindowSystem::createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot)
    {
        return new MacOSCursor(imageData, width, height, xHotSpot, yHotSpot);
    }

    const String& MacOSWindowSystem::getClipboardString()
    {
        @autoreleasepool
        {
            NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
            clipboardData = "";

            if (![[pasteboard types] containsObject:NSPasteboardTypeString])
            {
                LOG_ERROR("Cocoa: Failed to retrieve string from pasteboard");
                return clipboardData;
            }

            NSString* object = [pasteboard stringForType:NSPasteboardTypeString];
            if (!object)
            {
                LOG_ERROR("Cocoa: Failed to retrieve object from pasteboard");
                return clipboardData;
            }

            clipboardData = [object UTF8String];

            return clipboardData;
        }
    }

    void MacOSWindowSystem::setClipboardString(const String& data)
    {
        @autoreleasepool
        {
            NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
            [pasteboard declareTypes:@[ NSPasteboardTypeString ] owner:nil];
            [pasteboard setString:@(data.cString()) forType:NSPasteboardTypeString];
        }
    }

    Window* MacOSWindowSystem::getWindowByName(const String& name)
    {
        auto res = windows.find(name.hash());
        if (res != windows.end())
        {
            return res->second;
        }
        return nullptr;
    }

    Window* MacOSWindowSystem::getWindowByID(int ID)
    {
        auto res = windows.find(ID);
        if (res != windows.end())
        {
            return res->second;
        }
        return nullptr;
    }

    void MacOSWindowSystem::destroyWindow(Window* window)
    {
        auto res = std::find_if(windows.begin(), windows.end(), [window](const auto& pair) { return pair.second == window; });
        if (res != windows.end())
        {
            windows.erase(res);
            window->close();
            delete window;
        }
    }
}