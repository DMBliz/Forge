#pragma once
#include "Texture2DResource.h"
#include "Texture.h"

namespace Forge
{

	class Texture2D : public Texture
	{
	public:
		Texture2D();
		~Texture2D();

		virtual void SetTexture(const byte* pixels);
		virtual void SetTexture(const Image& img);

		void Load(String filename) override;
		void UnLoad() override;
	};

}
