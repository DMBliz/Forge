#pragma once
#include "Graphics/Texture2DResource.h"

namespace Forge
{
	class Image;

	class GLTexture2DResource : public Texture2DResource
	{
	private:
		uint ConvertToOGL(TextureInternalFormat internalFormat);
		uint ConvertToOGL(TextureFormat format);
		uint ConvertToOGL(TextureFilter filter);
		uint ConvertToOGL(TextureWrap wrap);
		uint ConvertToOGL(TextureDataType dataType);
	public:
		GLTexture2DResource();
		GLTexture2DResource(const Image& img, TextureParametrs params);
		GLTexture2DResource(const byte* pixels, uint width, uint height, TextureParametrs params);
		~GLTexture2DResource();

		void SetTexture(const Image& img) override;
		void SetTexture(const byte* pixels, const Vector2i& imgSize) override;
		void SetParameters(TextureParametrs params) override;

		void Bind(uint slot = 0) const override;
		void UnBind(uint slot = 0) const override;

		void CreateOnGPU(uint width, uint height, bool generateMipMaps, TextureParametrs params) override;
        void CreateOnGPU(const byte* pixels, uint width, uint height, bool generateMipMaps, TextureParametrs params) override;
        void CreateOnGPU(const Image& image, bool generateMipMaps, TextureParametrs params) override;

		void Load(Image image) override;
		void Load(Image image, TextureParametrs parametrs) override;
		void UnLoad() override;
	};
}
