#include "Vector2i.h"

namespace Forge
{

	Vector2i::Vector2i()
		: x(0), y(0)
	{}

	Vector2i::Vector2i(int x, int y)
		: x(x), y(y)
	{}

	Vector2i::Vector2i(const Vector2i& rhs)
		: x(rhs.x), y(rhs.y)
	{}


	void Vector2i::operator=(const Vector2i& rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	bool Vector2i::operator==(const Vector2i& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool Vector2i::operator!=(const Vector2i& rhs) const
	{
		return x != rhs.x && y != rhs.y;
	}


	Vector2i Vector2i::operator-() const
	{
		return Vector2i(-x, -y);
	}


	Vector2i Vector2i::operator+(const Vector2i& rhs) const
	{
		return Vector2i(x + rhs.x, y + rhs.y);
	}

	Vector2i Vector2i::operator-(const Vector2i& rhs) const
	{
		return Vector2i(x - rhs.x, y - rhs.y);
	}

	Vector2i Vector2i::operator*(const Vector2i& rhs) const
	{
		return Vector2i(x * rhs.x, y * rhs.y);
	}

	Vector2i Vector2i::operator*(int rhs) const
	{
		return Vector2i(x * rhs, y * rhs);
	}

	Vector2i operator*(int lhs, const Vector2i& rhs)
	{
		return rhs * lhs;
	}

	Vector2i Vector2i::operator/(const Vector2i& rhs) const
	{
		return Vector2i(x / rhs.x, y / rhs.y);
	}

	Vector2i Vector2i::operator/(int rhs) const
	{
		return Vector2i(x / rhs, y / rhs);
	}


	Vector2i& Vector2i::operator+=(const Vector2i& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2i& Vector2i::operator-=(const Vector2i& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2i& Vector2i::operator*=(const Vector2i& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2i& Vector2i::operator*=(int rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2i& Vector2i::operator/=(const Vector2i& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;

		return *this;
	}

	Vector2i& Vector2i::operator/=(int rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}


	float Vector2i::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	String Vector2i::ToString() const
	{
		return "(" + String(x) + ", " + String(y) + ")";
	}

}
