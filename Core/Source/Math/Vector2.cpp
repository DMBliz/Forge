#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mathf.h"

namespace Forge 
{
	const Vector2 Vector2::Zero;
	const Vector2 Vector2::One(1.0f, 1.0f);
	const Vector2 Vector2::Left(-1.0f, 0.0f);
	const Vector2 Vector2::Right(1.0f, 0.0f);
	const Vector2 Vector2::Up(0.0f, 1.0f);
	const Vector2 Vector2::Down(0.0f, -1.0f);

	Vector2::Vector2()
		: x(0.0f), y(0.0f)
	{}

	Vector2::Vector2(float x, float y)
		: x(x), y(y)
	{}

	Vector2::Vector2(const Vector2& vec)
		: x(vec.x), y(vec.y)
	{}

	Vector2::Vector2(const Vector3& vec)
		: x(vec.x), y(vec.y)
	{}

	Vector2::Vector2(const Vector4& vec)
		: x(vec.x), y(vec.y)
	{}

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return Vector2( + rhs.x, y + rhs.y);
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 Vector2::operator*(const Vector2& rhs) const
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}

	Vector2 Vector2::operator*(float rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

	Vector2 operator*(float lhs, Vector2 rhs)
	{
		return Vector2(lhs * rhs.x, lhs * rhs.y);
	}

	Vector2 Vector2::operator/(const Vector2& rhs) const
	{
		return Vector2(x / rhs.x, y / rhs.y);
	}

	Vector2 Vector2::operator/(float rhs) const
	{
		return Vector2(x / rhs, y / rhs);
	}

	Vector2& Vector2::operator=(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}

	bool Vector2::operator==(const Vector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool Vector2::operator!=(const Vector2& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2& Vector2::operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;

		return *this;
	}

	Vector2& Vector2::operator/=(float rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	Vector2 Vector2::Normalized() const
	{
		float lensq = LengthSquared();
		if (Equals(lensq, 1.0f) && lensq > 0.0f)
		{
			float invLen = 1.0f / sqrtf(lensq);
			return *this * invLen;
		}
		else
			return *this;
	}

	void Vector2::Normalize()
	{
		float lensq = LengthSquared();
		if (Equals(lensq, 1.0f) && lensq > 0.0f)
		{
			float invLen = 1.0f / sqrtf(lensq);
			x *= invLen;
			y *= invLen;
		}
	}

	float Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	float Vector2::LengthSquared() const
	{
		return x * x + y * y;
	}

	float Vector2::Dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	float Vector2::AbsDot(const Vector2& rhs) const
	{
		return Forge::Abs(x * rhs.x) + Forge::Abs(y * rhs.y);
	}

	float Vector2::ProjectOntoAxis(const Vector2& axis) const
	{
		return Dot(axis.Normalized());
	}

	float Vector2::Angle(const Vector2& rhs) const
	{
		return Acos(Dot(rhs) / (Length() * rhs.Length()));
	}

	Vector2 Vector2::Abs()
	{
		return Vector2(Forge::Abs(x), Forge::Abs(y));
	}

	Vector2 Vector2::Lerp(const Vector2& rhs, float t) const
	{
		return *this * (1.0f - t) + rhs * t;
	}

	Vector2 Lerp(const Vector2& lhs, const Vector2& rhs, const Vector2& t)
	{
		return lhs * (rhs - lhs) * t;
	}

	Vector2 Max(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(Forge::Max(lhs.x, rhs.x), Forge::Max(lhs.y, rhs.y));
	}

	Vector2 Min(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(Forge::Min(lhs.x, rhs.x), Forge::Min(lhs.y, rhs.y));
	}

	Vector2 Floor(const Vector2& vec)
	{
		return Vector2(Forge::Floor(vec.x), Forge::Floor(vec.x));
	}

	Vector2 Round(const Vector2& vec)
	{
		return Vector2(Forge::Round(vec.x), Forge::Round(vec.y));
	}

	Vector2 Ceil(const Vector2& vec)
	{
		return Vector2(Forge::Ceil(vec.x), Forge::Ceil(vec.y));
	}

	String Vector2::ToString() const
	{
		return "(" + String(x) + ", " + String(y) + ")";
	}
}
