#include "Renderer.h"
#include "OpenGL/Windows/OGLWIN32Context.h"
#include "Defines.h"
#include "Platform/Window.h"

namespace Forge
{

	void Renderer::Init(Window win)
	{
#if defined(WIN32)
#if defined(OGL)
		singleton = new OGLWIN32Context();
#elif defined(DIRECTX)
#endif
#elif defined(MACOS)
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		singleton->Init(win, 1, false, false);
	}

	Renderer::Renderer()
	{}

	Renderer::~Renderer()
	{}

}
