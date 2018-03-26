#pragma once
#include "Scene/Component.h"
#include "Graphics/Sprite.h"

namespace Forge
{
	class Texture2D;

	class SpriteRenderer : public Component
	{
	private:
		Sprite* sprite;
        bool _flipedX = false;
        bool _flipedY = false;
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void SetTexture(Texture2D* texture);
		Texture2D* GetTexture() const;

        Sprite* GetSprite() { return sprite; }

        void FlipX();
        void FlipY();

        bool IsFlipedX() const { return _flipedX; }
        bool IsFlipedY() const { return _flipedY; }

        void Update() override;
		void OnEnable() override;
		void OnDisable() override;
	};

}
