#include "Texture2DResource.h"
#include "OpenGL/OGLTexture2DResource.h"
#include "Resources/Image.h"

namespace Forge
{
	Texture2DResource* Texture2DResource::Create(const Image& img, TextureParametrs params)
	{
#if defined(OGL)
		return new OGLTexture2DResource(img, params);
#elif defined(DX)
#endif
	}
}
