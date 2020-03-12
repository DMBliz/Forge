//
// Created by Дмитрий Метелица on 2019-11-23.
//

#include "Platform/Api/WindowSystem.h"
#include "OSXWindow.h"
#include "OSXCursor.h"

namespace Forge
{

    void WindowSystem::init()
    {
    }

    Window* WindowSystem::createWindow(const WindowCreationDesc& desc)
    {
        OSXWindow* window;
        window = new OSXWindow();
        window->create(desc);
        return window;
    }

    WindowSystem::~WindowSystem()
    {

    }

    Cursor* WindowSystem::createCursor(SystemCursor cursorType)
    {
        return new OSXCursor(cursorType);
    }

    Cursor* WindowSystem::createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot)
    {
        return new OSXCursor(imageData, width, height, xHotSpot, yHotSpot);
    }
}