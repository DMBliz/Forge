#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Material.h"
#include "Drawable.h"
#include "Texture2D.h"

namespace Forge
{

	class Sprite : public Drawable
	{
	private:
		Vector2 _pivot;
		Color _color;
        Texture2D* _texture;
	public:
		Sprite();
		~Sprite();

		void SetTexture(Texture2D* texture);
		void SetMaterial(Material* material);
		void SetColor(const Color& color);
		void SetPivotPosition(const Vector2& pivot);

        void Draw() const override;

		Texture2D* GetTexture() const { return _texture; }
	};

}
