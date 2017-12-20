#pragma once
#include "Component.h"
#include "Graphics/Sprite.h"

namespace Forge
{
	class Texture2D;

	class SpriteRenderer : public Component
	{
	private:
		Sprite* sprite;
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void SetTexture(Texture2D* texture);

		void OnEnable() override;
		void OnDisable() override;
	};

}
