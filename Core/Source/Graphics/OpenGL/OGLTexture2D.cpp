#include "OGLTexture2D.h"
#include "Graphics/Image.h"
#include "glad/glad.h"
#include "GLCheck.h"
#include "Defines.h"

namespace Forge
{
	
	OGLTexture2D::OGLTexture2D(const Image& img, TextureParametrs params)
	{
		parametrs = params;
		size = img.GetSize();
		Load(img.GetPixels(), size.x, size.y);
	}

	OGLTexture2D::OGLTexture2D(const byte* pixels, uint width, uint height, TextureParametrs params)
	{
		parametrs = params;
		size = Vector2i(width, height);
		Load(pixels, width, height);
	}

	OGLTexture2D::~OGLTexture2D()
	{
		glCheck(glDeleteTextures(1, &textureID));
	}

	void OGLTexture2D::Load(const byte* pixels, uint width, uint height)
	{
		glCheck(glGenTextures(1, &textureID));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToOGL(parametrs.wrap)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToOGL(parametrs.wrap)));

		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, ConvertToOGL(parametrs.format), width, height, 0, ConvertToOGL(parametrs.format),
					 GL_UNSIGNED_BYTE, pixels));

		glCheck(glGenerateMipmap(GL_TEXTURE_2D));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));


	}

	uint OGLTexture2D::ConvertToOGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
			default: return 0;
		}
	}

	uint OGLTexture2D::ConvertToOGL(TextureFilter filter)
	{
		switch (filter)
		{
			case TextureFilter::Linear: return GL_LINEAR;
			case TextureFilter::Nearest: return GL_NEAREST;
			default: return 0;
		}
	}

	uint OGLTexture2D::ConvertToOGL(TextureWrap wrap)
	{
		switch (wrap)
		{
			case TextureWrap::Clamp_to_Edge: return GL_CLAMP_TO_EDGE;
			case TextureWrap::Clamp_to_border: return GL_CLAMP_TO_BORDER;
			case TextureWrap::Mirrored_Repeat: return GL_MIRRORED_REPEAT;
			case TextureWrap::Repeat: return GL_REPEAT;
			default: return 0;
		}
	}

	void OGLTexture2D::SetTexture(const Image& img)
	{
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, ConvertToOGL(parametrs.format), GL_UNSIGNED_BYTE, img.GetPixels()));
	}

	void OGLTexture2D::SetTexture(const byte* pixels)
	{
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, ConvertToOGL(parametrs.format), GL_UNSIGNED_BYTE, pixels));
	}

	void OGLTexture2D::Bind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
	}

	void OGLTexture2D::UnBind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
