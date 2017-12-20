#pragma once
#include "Texture.h"
#include "Math/Vector2i.h"

namespace Forge
{
	class Image;

	class Texture2D : public Texture
	{
	protected:
		Vector2i size;
	public:

		virtual void SetTexture(const byte* pixels) = 0;
		virtual void SetTexture(const Image& img) = 0;

		static Texture2D* Create(const Image& img, TextureParametrs params);
		static Texture2D* Create(const byte* pixels, uint width, uint height, TextureParametrs params);
	};

}
