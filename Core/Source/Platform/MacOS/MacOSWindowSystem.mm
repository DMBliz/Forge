//
// Created by Dmitry Metelitsa on 2019-11-23.
//

#include "Platform/Api/WindowSystem.h"
#include "MacOSWindow.h"
#include "MacOSCursor.h"

namespace Forge
{

    void WindowSystem::init()
    {

    }

    Window* WindowSystem::createWindow(const WindowCreationDesc& desc)
    {
        MacOSWindow* window;
        window = new MacOSWindow();
        window->create(desc);
        return window;
    }

    WindowSystem::~WindowSystem()
    {

    }

    Cursor* WindowSystem::createCursor(SystemCursor cursorType)
    {
        return new MacOSCursor(cursorType);
    }

    Cursor* WindowSystem::createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot)
    {
        return new MacOSCursor(imageData, width, height, xHotSpot, yHotSpot);
    }

    const String& WindowSystem::getClipboardString()
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

    void WindowSystem::setClipboardString(const String& data)
    {
        @autoreleasepool
        {
            NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
            [pasteboard declareTypes:@[ NSPasteboardTypeString ] owner:nil];
            [pasteboard setString:@(data.CString()) forType:NSPasteboardTypeString];
        }
    }
}