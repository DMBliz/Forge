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
		Material* _material;
		Vector2 _pivot;
		Color _color;
	public:
		Sprite();
		~Sprite();

		void SetTexture(Texture2D* texture);
		void SetMaterial(Material* material);
		void SetColor(const Color& color);
		void SetPivotPosition(const Vector2& pivot);
		void SetPosition(const Matrix3x4& position);

		Texture2D* GetTexture() const { return static_cast<Texture2D*>(_material->GetTexture("spriteTexture")); }
	};

}
