#include "Rect.h"
#include "Vector4.h"

namespace Forge
{

	Rect::Rect()
		: min(0.0f, 0.0f), max(0.0f, 0.0f)
	{}


	Rect::Rect(const Vector2& min, const Vector2& max)
		: min(min), max(max)
	{}

	Rect::Rect(float x, float y, float width, float height)
		: min(x, y), max(x + width, y + height)
	{}

	Rect::Rect(const Vector4& vector)
		: min(vector.x, vector.y), max(vector.z, vector.w)
	{}

	Rect::Rect(const Rect& rect)
		: min(rect.min), max(rect.max)
	{}

	Rect& Rect::operator=(const Rect& rhs)
	{
		min = rhs.min;
		max = rhs.max;

		return *this;
	}

	bool Rect::operator==(const Rect& rhs) const
	{
		return min == rhs.min && max == rhs.max;
	}

	bool Rect::operator!=(const Rect& rhs) const
	{
		return min != rhs.min || max != rhs.max;
	}

	void Rect::Set(const Rect& rect)
	{
		min = rect.min;
		max = rect.max;
	}

	void Rect::Set(const Vector2& min, const Vector2& max)
	{
		this->min = min;
		this->max = max;
	}

	Vector2 Rect::Center() const
	{
		return Vector2(max + min) * 0.5f;
	}

	Vector2 Rect::Size() const
	{
		return max - min;
	}

	Vector4 Rect::ToVector4() const
	{
		return Vector4(min.x, min.y, max.x, max.y);
	}

	String Rect::ToString() const
	{
		return "(" + String(min.x) + ", " + String(min.x) + ", " 
			+ String(max.x) + ", " + String(max.x) + ")\n";
	}

}
