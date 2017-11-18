#include "Color.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Forge
{
	Color::Color(const Vector3& vec)
		: r(vec.x * 255.0f), g(vec.y * 255.0f), b(vec.z * 255.0f), a(255)
	{}

	Color::Color(const Vector3& vec, unsigned char alpha)
		: r(vec.x * 255.0f), g(vec.y * 255.0f), b(vec.z * 255.0f), a(a)
	{}

	Color::Color(const Vector4& vec)
		: r(vec.x * 255.0f), g(vec.y * 255.0f), b(vec.z * 255.0f), a(vec.w * 255.0f)
	{}

	Color& Color::operator=(const Color& rhs)
	{
		rgba = rhs.rgba;

		return *this;
	}

	Color& Color::operator=(const Vector3& rhs)
	{
		r = rhs.x * 255.0f;
		g = rhs.y * 255.0f;
		b = rhs.z * 255.0f;
		a = 255;

		return *this;
	}

	Color& Color::operator=(const Vector4& rhs)
	{
		r = rhs.x * 255.0f;
		g = rhs.y * 255.0f;
		b = rhs.z * 255.0f;
		a = rhs.w * 255.0f;

		return *this;
	}

	bool Color::operator==(const Color& rhs)
	{
		return rgba == rhs.rgba;
	}

	bool Color::operator!=(const Color& rhs)
	{
		return rgba != rhs.rgba;
	}
}
