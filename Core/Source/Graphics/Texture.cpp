#include "Texture.h"
#include "Texture2DResource.h"

namespace Forge
{

	Texture::Texture()
	{
		
	}


	Texture::~Texture()
	{}

	void Texture::Bind(uint slot)
	{
		textureResource->Bind(slot);
	}

	void Texture::UnBind(uint slot) const
	{
		textureResource->UnBind(slot);
	}

	void Texture::SetParameters(TextureParametrs params)
	{
		textureResource->SetParameters(params);
	}
}
