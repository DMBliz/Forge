#include "Texture2D.h"
#include "OpenGL/OGLTexture2D.h"
#include "Image.h"

namespace Forge
{
	Texture2D* Texture2D::Create(const Image& img, TextureParametrs params)
	{
#if defined(OGL)
		return new OGLTexture2D(img, params);
#elif defined(DX)
#endif
	}

	Texture2D* Texture2D::Create(const byte* pixels, uint width, uint height, TextureParametrs params)
	{
#if defined(OGL)
		return new OGLTexture2D(pixels, width, height, params);
#elif defined(DX)
#endif
	}
}
