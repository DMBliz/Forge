#include "Texture2DResource.h"
#include "OGL/GLTexture2DResource.h"
#include "Resources/Image.h"

namespace Forge
{

	Texture2DResource* Texture2DResource::Create()
	{
#if defined(OGL)
		return new GLTexture2DResource();
#elif defined(DX)
#endif
	}

	Texture2DResource* Texture2DResource::Create(const Image& img, TextureParametrs params)
	{
#if defined(OGL)
		return new GLTexture2DResource(img, params);
#elif defined(DX)
#endif
	}
}
