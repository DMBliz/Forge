#include "Vector4.h"
#include "Mathf.h"

namespace Forge
{
	const Vector4 Vector4::Zero;
	const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);


	Vector4::Vector4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vector4::Vector4(const Vector2& vec)
		: x(vec.x), y(vec.y), z(0.0f), w(0.0f)
	{}

	Vector4::Vector4(const Vector2& vec, float z, float w)
		: x(vec.x), y(vec.y), z(z), w(w)
	{}

	Vector4::Vector4(const Vector3& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(0.0f)
	{}

	Vector4::Vector4(const Vector3& vec, float w)
		: x(vec.x), y(vec.y), z(vec.z), w(w)
	{}

	Vector4::Vector4(const Vector4& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
	{}

	Vector4 Vector4::operator+(const Vector4& rhs) const
	{
		return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vector4 Vector4::operator-(const Vector4& rhs) const
	{
		return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Vector4 Vector4::operator*(const Vector4& rhs) const
	{
		return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	Vector4 Vector4::operator*(float rhs) const
	{
		return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	Vector4 operator*(float lhs, Vector4 rhs)
	{
		return rhs;
	}

	Vector4 Vector4::operator/(const Vector4& rhs) const
	{
		return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	Vector4 Vector4::operator/(const float rhs) const
	{
		return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	Vector4& Vector4::operator=(const Vector4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *this;
	}

	bool Vector4::operator==(const Vector4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	bool Vector4::operator!=(const Vector4& rhs) const
	{
		return x != rhs.x && y != rhs.y && z != rhs.z && w != rhs.w;

	}
	
	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;

		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;

		return *this;
	}

	Vector4& Vector4::operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;

		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;

		return *this;
	}

	Vector4& Vector4::operator/=(float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;

		return *this;
	}

	float Vector4::Dot(const Vector4& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	float Vector4::AbsDot(const Vector4& rhs) const
	{
		return Forge::Abs(x * rhs.x) + Forge::Abs(y * rhs.y) + Forge::Abs(z * rhs.z) + Forge::Abs(w * rhs.w);
	}

	float Vector4::ProjectOntoAxis(const Vector3& axis) const
	{
		return Dot(Vector4(axis.Normalized()));
	}

	Vector4 Vector4::Abs() const
	{
		return Vector4(Forge::Abs(x), Forge::Abs(y), Forge::Abs(z), Forge::Abs(w));
	}

	Vector4 Vector4::Lerp(const Vector4& rhs, float t) const
	{
		return *this * (1.0f - t) + rhs * t;
	}

	Vector4 Lerp(const Vector4& lhs, const Vector4& rhs, const Vector4& t)
	{
		return lhs * (rhs - lhs) * t;
	}

	Vector4 Max(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(Forge::Max(lhs.x, rhs.x), Forge::Max(lhs.y, rhs.y), Forge::Max(lhs.z, rhs.z), Forge::Max(lhs.w, rhs.w));
	}

	Vector4 Min(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(Forge::Min(lhs.x, rhs.x), Forge::Min(lhs.y, rhs.y), Forge::Min(lhs.z, rhs.z), Forge::Min(lhs.w, rhs.w));
	}

	Vector4 Floor(const Vector4& rhs)
	{
		return Vector4(Forge::Floor(rhs.x), Forge::Floor(rhs.y), Forge::Floor(rhs.z), Forge::Floor(rhs.w));
	}

	Vector4 Round(const Vector4& rhs)
	{
		return Vector4(Forge::Round(rhs.x), Forge::Round(rhs.y), Forge::Round(rhs.z), Forge::Round(rhs.w));
	}

	Vector4 Ceil(const Vector4& rhs)
	{
		return Vector4(Forge::Ceil(rhs.x), Forge::Ceil(rhs.y), Forge::Ceil(rhs.z), Forge::Ceil(rhs.w));
	}

	String Vector4::ToString() const
	{
		return "(" + String(x) + ", " + String(y) + ", " + String(z) + ", " + String(w) + ")";
	}
}
