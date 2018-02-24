#include "RenderSurface.h"
#include "OpenGL/GLRenderSurface.h"

namespace Forge
{
	void RenderSurface::Resize(const Vector2i& newSize)
	{
		size = newSize;
	}

	const Color& RenderSurface::GetClearColor() const
	{
		return ClearColor;
	}

	void RenderSurface::SetClearColor(const Color& newColor)
	{
		ClearColor = newColor;
	}

	RenderSurface* RenderSurface::Create()
	{

#if defined(OGL)
		return new GLRenderSurface();
#elif defined(DX)
#endif
	}

}
