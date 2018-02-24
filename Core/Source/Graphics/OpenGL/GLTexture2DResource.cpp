#include "GLTexture2DResource.h"
#include "Resources/Image.h"
#include "glad/glad.h"
#include "GLCheck.h"

namespace Forge
{
	GLTexture2DResource::GLTexture2DResource()
	{}

	GLTexture2DResource::GLTexture2DResource(const Image& img, TextureParametrs params)
	{
		parametrs = params;
		size = img.GetSize();
		LoadToGpu(img.GetPixels(), size.x, size.y);
	}

	GLTexture2DResource::GLTexture2DResource(const byte* pixels, uint width, uint height, TextureParametrs params)
	{
		parametrs = params;
		size = Vector2i(width, height);
		LoadToGpu(pixels, width, height);
	}

	GLTexture2DResource::~GLTexture2DResource()
	{
		UnLoad();
	}

	void GLTexture2DResource::LoadToGpu(const byte* pixels, uint width, uint height)
	{
		glCheck(glGenTextures(1, &textureID));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToOGL(parametrs.wrap)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToOGL(parametrs.wrap)));

		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, ConvertToOGL(parametrs.internalFormat), width, height, 0, 
				ConvertToOGL(parametrs.format), ConvertToOGL(parametrs.dataType), pixels));

		glCheck(glGenerateMipmap(GL_TEXTURE_2D));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}

	uint GLTexture2DResource::ConvertToOGL(TextureInternalFormat internalFormat)
	{
		switch (internalFormat)
		{
			case TextureInternalFormat::RGB: return GL_RGB;
			case TextureInternalFormat::RGBA: return GL_RGBA;
			case TextureInternalFormat::DepthStencil: return GL_DEPTH24_STENCIL8;
			default: return 0;
		}
	}

	uint GLTexture2DResource::ConvertToOGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
			case TextureFormat::DepthStencil: return GL_DEPTH_STENCIL;
			default: return 0;
		}
	}

	uint GLTexture2DResource::ConvertToOGL(TextureFilter filter)
	{
		switch (filter)
		{
			case TextureFilter::Linear: return GL_LINEAR;
			case TextureFilter::Nearest: return GL_NEAREST;
			default: return 0;
		}
	}

	uint GLTexture2DResource::ConvertToOGL(TextureWrap wrap)
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

	uint GLTexture2DResource::ConvertToOGL(TextureDataType dataType)
	{
		switch (dataType)
		{
			case TextureDataType::Byte: return GL_UNSIGNED_BYTE;
			case TextureDataType::UnsignedInt: return GL_UNSIGNED_INT;
			case TextureDataType::UnsignedInt_24_8: return GL_UNSIGNED_INT_24_8;
			default: return 0;
		}
	}

	void GLTexture2DResource::SetTexture(const Image& img)
	{
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, ConvertToOGL(parametrs.internalFormat), size.x, size.y, 0,
				ConvertToOGL(parametrs.format), ConvertToOGL(parametrs.dataType), img.GetPixels()));
	}

	void GLTexture2DResource::SetTexture(const byte* pixels, const Vector2i& imgSize)
	{
		size = imgSize;
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, ConvertToOGL(parametrs.internalFormat), size.x, size.y, 0,
				ConvertToOGL(parametrs.format), ConvertToOGL(parametrs.dataType), pixels));
	}

	void GLTexture2DResource::SetParameters(TextureParametrs params)
	{
		parametrs = params;
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToOGL(parametrs.wrap)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToOGL(parametrs.wrap)));
	}

	void GLTexture2DResource::Bind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
	}

	void GLTexture2DResource::UnBind(uint slot) const
	{
		glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GLTexture2DResource::CreateOnGPU(uint width, uint height, TextureParametrs params, bool generateMipMaps)
	{
		Texture2DResource::CreateOnGPU(width, height, params, generateMipMaps);
		glCheck(glGenTextures(1, &textureID));
		glCheck(glBindTexture(GL_TEXTURE_2D, textureID));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToOGL(parametrs.filter)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertToOGL(parametrs.wrap)));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertToOGL(parametrs.wrap)));

		glTexImage2D(GL_TEXTURE_2D, 0, ConvertToOGL(parametrs.internalFormat), width, height, 0,
				ConvertToOGL(parametrs.format), ConvertToOGL(parametrs.dataType), nullptr);

		if (generateMipMaps)
			glCheck(glGenerateMipmap(GL_TEXTURE_2D));
		glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GLTexture2DResource::Load(Image image)
	{
		LoadToGpu(image.GetPixels(), image.GetSize().x, image.GetSize().y);
	}

	void GLTexture2DResource::Load(Image image, TextureParametrs params)
	{
		parametrs = params;
		LoadToGpu(image.GetPixels(), image.GetSize().x, image.GetSize().y);
	}

	void GLTexture2DResource::UnLoad()
	{
		glCheck(glDeleteTextures(1, &textureID));
	}
}
