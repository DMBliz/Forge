#include "Context.h"
#include "Platform/Window.h"

namespace Forge
{

	Context::Context()
	{}

	void Context::Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer)
	{
		size = win.GetWindowSize();
		this->sampleCount = sampleCount;
		this->depth = depth;
		this->debugRenderer = debugRenderer;
	}

}
