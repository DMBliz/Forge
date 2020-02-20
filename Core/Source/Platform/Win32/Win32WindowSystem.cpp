#include "Platform/Api/WindowSystem.h"
#include "Win32Window.h"

namespace Forge
{

    void WindowSystem::init()
    {
    }

    Window* WindowSystem::createWindow(const WindowCreationDesc& desc)
    {
        Win32Window* window = new Win32Window();
        window->create(desc);
        return window;
    }

    WindowSystem::~WindowSystem()
    {

    }
}