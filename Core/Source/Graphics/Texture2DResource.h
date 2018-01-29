#pragma once
#include "TextureResource.h"
#include "Math/Vector2i.h"

namespace Forge
{
	class Image;

	class Texture2DResource : public TextureResource
	{
	protected:
		Vector2i size;
	public:

		virtual void SetTexture(const byte* pixels) = 0;
		virtual void SetTexture(const Image& img) = 0;
		
		void Bind(uint slot) const override = 0;
		void UnBind(uint slot) const override = 0;
		void SetParameters(TextureParametrs params) override = 0;

		virtual void Load(Image image) = 0;
		virtual void Load(Image image, TextureParametrs parametrs) = 0;
		virtual void UnLoad() = 0;

		static Texture2DResource* Create(const Image& img, TextureParametrs params);
	};

}
