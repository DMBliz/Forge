#include "Vector3.h"
#include "Mathf.h"

namespace Forge
{
	const Vector3 Vector3::Zero;
	const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
	const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::Back(0.0f, 0.0f, -1.0f);

	Vector3::Vector3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vector3::Vector3(const Vector2& vec)
		: x(vec.x), y(vec.y), z(0.0f)
	{}

	Vector3::Vector3(const Vector2& vec, float z)
		: x(vec.x), y(vec.y), z(z)
	{}

	Vector3::Vector3(const Vector3& vec)
		: x(vec.x), y(vec.y), z(vec.z)
	{}

	Vector3::Vector3(const Vector4& vec)
		: x(vec.x), y(vec.y), z(vec.z)
	{}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 Vector3::operator*(const Vector3& rhs) const
	{
		return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Vector3 Vector3::operator*(const float rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	Vector3 operator*(float lhs, Vector3 rhs)
	{
		rhs.x *= lhs;
		rhs.y *= lhs;
		rhs.z *= lhs;

		return rhs;
	}

	Vector3 Vector3::operator/(const Vector3& rhs) const
	{
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	Vector3 Vector3::operator/(float rhs) const
	{
		return Vector3(x / rhs, y / rhs, z / rhs);
	}

	Vector3& Vector3::operator=(const Vector3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	bool Vector3::operator==(const Vector3& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool Vector3::operator!=(const Vector3& rhs) const
	{
		return x != rhs.x && y != rhs.y && z != rhs.z;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;

		return *this;
	}

	Vector3& Vector3::operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;

		return *this;
	}

	Vector3& Vector3::operator/=(float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;

		return *this;
	}

	Vector3 Vector3::Normalized() const
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

	void Vector3::Normalize()
	{
		float lensq = LengthSquared();
		if (Equals(lensq, 1.0f) && lensq > 0.0f)
		{
			float invLen = 1.0f / sqrtf(lensq);
			x *= invLen;
			y *= invLen;
			z *= invLen;
		}
	}

	float Vector3::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float Vector3::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3::Dot(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	float Vector3::AbsDot(const Vector3& rhs) const
	{
		return Forge::Abs(x * rhs.x) + Forge::Abs(y * rhs.y) + Forge::Abs(z * rhs.z);
	}

	Vector3 Vector3::Cross(const Vector3& rhs) const
	{
		return Vector3(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		);
	}

	Vector3 Vector3::Orthogonalize(const Vector3& axis) const
	{
		return axis.Cross(*this).Cross(axis).Normalized();
	}

	float Vector3::ProjectOntoAxis(const Vector3& axis) const
	{
		return Dot(axis.Normalized());
	}

	float Vector3::Angle(const Vector3& rhs) const
	{
		return Acos(Dot(rhs) / (Length() * rhs.Length()));
	}

	Vector3 Vector3::Abs()
	{
		return Vector3(Forge::Abs(x), Forge::Abs(y), Forge::Abs(z));
	}

	Vector3 Vector3::Lerp(const Vector3& rhs, float t) const
	{
		return *this * (1.0f - t) + rhs * t;
	}

	Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, const Vector3& t)
	{
		return lhs * (rhs - lhs) * t;
	}

	Vector3 Max(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(Forge::Max(lhs.x, rhs.x), Forge::Max(lhs.y, rhs.y), Forge::Max(lhs.z, rhs.z));
	}

	Vector3 Min(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(Forge::Min(lhs.x, rhs.x), Forge::Min(lhs.y, rhs.y), Forge::Min(lhs.z, rhs.z));
	}

	Vector3 Floor(const Vector3& vec)
	{
		return Vector3(Forge::Floor(vec.x), Forge::Floor(vec.x), Forge::Floor(vec.z));
	}

	Vector3 Round(const Vector3& vec)
	{
		return Vector3(Forge::Round(vec.x), Forge::Round(vec.y), Forge::Round(vec.z));
	}

	Vector3 Ceil(const Vector3& vec)
	{
		return Vector3(Forge::Ceil(vec.x), Forge::Ceil(vec.y), Forge::Ceil(vec.z));
	}

	String Vector3::ToString() const
	{
		return "(" + String(x) + ", " + String(y) + ", " + String(z) + ")";
	}
}
