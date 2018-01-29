#include "GraphicsRenderer.h"
#include "Platform/Window.h"
#include "OpenGL/OGLGraphicsRenderer.h"

namespace Forge
{

	GraphicsRenderer::GraphicsRenderer()
	{
	}


	GraphicsRenderer::~GraphicsRenderer()
	{}

	void GraphicsRenderer::Init(const Window& win)
	{
		size = win.GetSize();
		this->sampleCount = sampleCount;
		this->depth = depth;
		this->debugRenderer = debugRenderer;
	}

	GraphicsRenderer* GraphicsRenderer::Create()
	{
#if defined(OGL)
		return new OGLGraphicsRenderer();
#elif defined(DX) //TODO: return for DX
		return nullptr;
#endif
	}
}
