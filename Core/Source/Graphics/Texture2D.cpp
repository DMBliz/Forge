#include "Texture2D.h"
#include "Resources/Resources.h"
#include "Resources/Image.h"

namespace Forge
{

	Texture2D::Texture2D()
	{}


	Texture2D::~Texture2D()
	{}

	void Texture2D::SetTexture(const byte* pixels)
	{
		static_cast<Texture2DResource*>(textureResource)->SetTexture(pixels);
	}

	void Texture2D::SetTexture(const Image& img)
	{
		static_cast<Texture2DResource*>(textureResource)->SetTexture(img);
	}

	void Texture2D::Load(String filename)
	{
		resourceName = filename;
		Image* img = Resources::Singleton()->LoadNowResource<Image>(filename);
		textureResource = Texture2DResource::Create(*img, TextureParametrs());
	}

	void Texture2D::UnLoad()
	{
		static_cast<Texture2DResource*>(textureResource)->UnLoad();
		delete textureResource;
	}
}
