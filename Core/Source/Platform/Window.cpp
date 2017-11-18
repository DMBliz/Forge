#include "Window.h"
#include "Defines.h"
#include "Windows/WindowWin32.h"

namespace Forge
{

	Window::Window()
	{}


	Window::~Window()
	{}

	void Window::Init()
	{
#if defined(WIN32)
		window = new WindowWin32();
#elif defined(MACOS)
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
	}
}
