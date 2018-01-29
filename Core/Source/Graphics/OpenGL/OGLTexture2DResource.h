#pragma once
#include "Graphics/Texture2DResource.h"

namespace Forge
{
	class Image;

	class OGLTexture2DResource : public Texture2DResource
	{
	private:
		void LoadToGpu(const byte* pixels, uint width, uint height);
		uint ConvertToOGL(TextureFormat format);
		uint ConvertToOGL(TextureFilter filter);
		uint ConvertToOGL(TextureWrap wrap);
	public:
		OGLTexture2DResource();
		OGLTexture2DResource(const Image& img, TextureParametrs params);
		OGLTexture2DResource(const byte* pixels, uint width, uint height, TextureParametrs params);
		~OGLTexture2DResource();

		void SetTexture(const Image& img) override;
		void SetTexture(const byte* pixels) override;
		void SetParameters(TextureParametrs params) override;

		void Bind(uint slot = 0) const override;
		void UnBind(uint slot = 0) const override;

		void Load(Image image) override;
		void Load(Image image, TextureParametrs parametrs) override;
		void UnLoad() override;
	};

}
