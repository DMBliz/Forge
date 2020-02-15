//
// Created by Дмитрий Метелица on 2019-11-23.
//

#include "Platform/Api/WindowSystem.h"
#include "OSXWindow.h"

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
}