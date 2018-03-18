#pragma once
#include "Texture2DResource.h"
#include "Texture.h"

namespace Forge
{

	class Texture2D : public Texture
	{
	public:
		Texture2D();
		~Texture2D();

		virtual void SetTexture(const byte* pixels, const Vector2i& imgSize);
		virtual void SetTexture(const Image& img);

		virtual void CreateOnGPU(uint width, uint height, TextureParametrs params, bool generateMipMaps);
		const Vector2i& GetSize() const { return static_cast<Texture2DResource*>(textureResource)->GetSize(); }
		void Load(const String& filename) override;
		void UnLoad() override;
	};

}
