#include "Window.h"
#include "Windows/WindowWin32.h"

namespace Forge
{
	Window* Window::GetInstance()
	{
		Window* ret;
#if defined(WIN32)
#if defined(OGL)
		ret = new WindowWin32();
#elif defined(DIRECTX)
#endif
#elif defined(MACOS)
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		return ret;
	}
}
