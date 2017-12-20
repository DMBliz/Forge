#pragma once
#include "Graphics/Texture2D.h"

namespace Forge
{
	class Image;

	class OGLTexture2D : public Texture2D
	{
	private:
		void Load(const byte* pixels, uint width, uint height);
		uint ConvertToOGL(TextureFormat format);
		uint ConvertToOGL(TextureFilter filter);
		uint ConvertToOGL(TextureWrap wrap);
	public:
		OGLTexture2D(const Image& img, TextureParametrs params);
		OGLTexture2D(const byte* pixels, uint width, uint height, TextureParametrs params);
		~OGLTexture2D();



		void SetTexture(const Image& img) override;
		void SetTexture(const byte* pixels) override;

		void Bind(uint slot = 0) const override;
		void UnBind(uint slot = 0) const override;
	};

}
