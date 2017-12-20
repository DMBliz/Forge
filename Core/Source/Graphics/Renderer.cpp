#include "Renderer.h"
#include "Platform/Window.h"
#include "OpenGL/OGLGraphicsRenderer.h"

namespace Forge
{

	void Renderer::Init(Window* win)
	{
#if defined(WIN32)
#if defined(OGL)
		deviceRenderer = new OGLGraphicsRenderer();
#elif defined(DX)
#endif
#elif defined(MACOS)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		deviceRenderer->Init(*win, 1, false, false);
	}

	Renderer::Renderer()
	{
		
	}

	Renderer::~Renderer()
	{
		for(uint i = 0; i < drawBatches.size(); i++)
		{
			delete drawBatches[i];
		}
	}

}
