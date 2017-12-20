#include "Color.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Forge
{
	Color::Color(const Vector3& vec) :
	r(static_cast<byte>(vec.x * 255.0f)), 
	g(static_cast<byte>(vec.y * 255.0f)), 
	b(static_cast<byte>(vec.z * 255.0f)), 
	a(255)
	{}

	Color::Color(const Vector3& vec, byte alpha) :
	r(static_cast<byte>(vec.x * 255.0f)),
	g(static_cast<byte>(vec.y * 255.0f)),
	b(static_cast<byte>(vec.z * 255.0f)),
	a(a)
	{}

	Color::Color(const Vector4& vec) :
	r(static_cast<byte>(vec.x * 255.0f)),
	g(static_cast<byte>(vec.y * 255.0f)),
	b(static_cast<byte>(vec.z * 255.0f)),
	a(static_cast<byte>(vec.w * 255.0f))
	{}

	Color& Color::operator=(const Color& rhs)
	{
		rgba = rhs.rgba;

		return *this;
	}

	Color& Color::operator=(const Vector3& rhs)
	{
		r = static_cast<byte>(rhs.x * 255.0f);
		g = static_cast<byte>(rhs.y * 255.0f);
		b = static_cast<byte>(rhs.z * 255.0f);
		a = 255;

		return *this;
	}

	Color& Color::operator=(const Vector4& rhs)
	{
		r = static_cast<byte>(rhs.x * 255.0f);
		g = static_cast<byte>(rhs.y * 255.0f);
		b = static_cast<byte>(rhs.z * 255.0f);
		a = static_cast<byte>(rhs.w * 255.0f);

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
