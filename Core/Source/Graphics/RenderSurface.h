#pragma once
#include "Types.h"
#include "Math/Vector2i.h"
#include "Texture2D.h"
#include "Math/Color.h"

namespace Forge
{

	class RenderSurface
	{
	protected:
		uint framebufferID = 0;
		uint depthStencilID = 0;
		Texture2D* colorTexture;
		Texture2D* depthStencilTexture;
		Vector2i size;
		Color ClearColor;

	public:
		RenderSurface()
			: size(600,800)
		{
			colorTexture = new Texture2D;
			depthStencilTexture = new Texture2D;
		}

		virtual void SetFramebufferSize(Vector2i newSize)
		{
			size = newSize;
		}

		const Vector2i& GetSize() const { return size; }

		virtual void Generate() = 0;
		virtual void Bind() = 0;

		virtual void Resize(const Vector2i& newSize);
		const Color& GetClearColor() const;
		void SetClearColor(const Color& newColor);
		Texture2D* GetColorTexture() const { return colorTexture; }
		Texture2D* GetDepthStencilTexture() const { return depthStencilTexture; }

		static RenderSurface* Create();
	};
}
