#pragma once
#include "Graphics/RenderSurface.h"

namespace Forge
{
	class GLRenderSurface : public RenderSurface
	{

	public:
		~GLRenderSurface();
		void Generate() override;
		void Bind() override;
		void Resize(const Vector2i& newSize) override;
	};
}
