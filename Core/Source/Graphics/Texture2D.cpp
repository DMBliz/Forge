#include "Texture2D.h"
#include "Resources/Resources.h"
#include "Resources/Image.h"
#include "Core/Engine.h"

namespace Forge
{

	Texture2D::Texture2D()
	{
		textureResource = Texture2DResource::Create();
	}

	Texture2D::~Texture2D()
	{}

	void Texture2D::SetTexture(const byte* pixels, const Vector2i& imgSize)
	{
		static_cast<Texture2DResource*>(textureResource)->SetTexture(pixels, imgSize);
	}

	void Texture2D::SetTexture(const Image& img)
	{
		static_cast<Texture2DResource*>(textureResource)->SetTexture(img);
	}

	void Texture2D::CreateOnGPU(uint width, uint height, TextureParametrs params, bool generateMipMaps)
	{
		static_cast<Texture2DResource*>(textureResource)->CreateOnGPU(width, height, generateMipMaps, params);
	}

    void Texture2D::CreateOnGPU(const Image& img, TextureParametrs params, bool generateMipMaps)
    {
        static_cast<Texture2DResource*>(textureResource)->Load(img, params);
    }

    void Texture2D::Load(const String& filename)
	{
		resourceName = filename;
		Image* img = engine->GetResources()->LoadNowResource<Image>(filename);
		textureResource = Texture2DResource::Create(*img, TextureParametrs(TextureFilter::Nearest));
	}

	void Texture2D::UnLoad()
	{
		static_cast<Texture2DResource*>(textureResource)->UnLoad();
		delete textureResource;
	}
}
