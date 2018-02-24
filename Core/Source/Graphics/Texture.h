#pragma once
#include "TextureResource.h"

namespace Forge
{

	class Texture : public Resource
	{
	protected:
		TextureResource* textureResource = nullptr;
	public:
		Texture();
		~Texture();

		uint GetID() const { return textureResource->GetID(); }

		virtual void Bind(uint slot = 0);
		virtual void UnBind(uint slot = 0) const;
		virtual void SetParameters(TextureParametrs params);

		void Load(String filename) override = 0;
		void UnLoad() override = 0;
	};

}
