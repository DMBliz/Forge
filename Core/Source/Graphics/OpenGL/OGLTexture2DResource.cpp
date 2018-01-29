#include "OGLTexture2DResource.h"
#include "Resources/Image.h"
#include "glad/glad.h"
#include "GLCheck.h"

namespace Forge
{
	OGLTexture2DResource::OGLTexture2DResource()
	{}

	OGLTexture2DResource::OGLTexture2DResource(const Image& img, TextureParametrs params)
	{
		parametrs = params;
		size = img.GetSize();
		LoadToGpu(img.GetPixels(), size.x, size.y);
	}

	OGLTexture2DResource::OGLTexture2DResource(const byte* pixels, uint width, uint height, TextureParametrs params)
	{
		parametrs = params;
		size = Vector2i(width, height);
		LoadToGpu(pixels, width, height);
	}

	OGLTexture2DResource::~OGLTexture2DResource()
	{
		UnLoad();
	}

	void OGLTexture2DResource::LoadToGpu(const byte* pixels, uint width, uint height)
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

	uint OGLTexture2DResource::ConvertToOGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
			default: return 0;
		}
	}

	uint OGLTexture2DResource::ConvertToOGL(TextureFilter filter)
	{
		switch (filter)
		{
			case TextureFilter::Linear: return GL_LINEAR;
			case TextureFilter::Nearest: return GL_NEAREST;
			default: return 0;
		}
	}

	uint OGLTexture2DResource::ConvertToOGL(TextureWrap wrap)
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

	void OGLTexture2DResource::SetTexture(const Image& img)
	{
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, ConvertToOGL(parametrs.format), GL_UNSIGNED_BYTE, img.GetPixels()));
	}

	void OGLTexture2DResource::SetTexture(const byte* pixels)
	{
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, ConvertToOGL(parametrs.format), GL_UNSIGNED_BYTE, pixels));
	}

	void OGLTexture2DResource::SetParameters(TextureParametrs params)
	{
		parametrs = params;
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToOGL(parametrs.wrap)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToOGL(parametrs.wrap)));
	}

	void OGLTexture2DResource::Bind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
	}

	void OGLTexture2DResource::UnBind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void OGLTexture2DResource::Load(Image image)
	{
		LoadToGpu(image.GetPixels(), image.GetSize().x, image.GetSize().y);
	}

	void OGLTexture2DResource::Load(Image image, TextureParametrs params)
	{
		parametrs = params;
		LoadToGpu(image.GetPixels(), image.GetSize().x, image.GetSize().y);
	}

	//TODO: unload texture
	void OGLTexture2DResource::UnLoad()
	{
		glCheck(glDeleteTextures(1, &textureID));
	}
}
