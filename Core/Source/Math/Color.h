#pragma once
#include "Containers/String.h"
#include "Vector4.h"
#include "Types.h"

namespace Forge
{
	class Vector3;


	class Color
	{
	public:
		union
		{
			uint rgba;
			struct
			{
				byte a;
				byte b;
				byte g;
				byte r;
			};
		};

		Color::Color()
			: rgba(0x00000000)
		{}

		Color::Color(uint color)
			: rgba(color)
		{}

		Color::Color(const Color& color)
			: rgba(color.rgba)
		{}

		Color::Color(int red, int green, int blue) : 
		a(255), 
		b(static_cast<byte>(blue)), 
		g(static_cast<byte>(green)), 
		r(static_cast<byte>(red))
		{}

		Color::Color(float red, float green, float blue) : 
		a(255), 
		b(static_cast<byte>(blue * 255.0f)), 
		g(static_cast<byte>(green * 255.0f)), 
		r(static_cast<byte>(red * 255.0f))
		{}

		Color::Color(int red, int green, int blue, int alpha) :
		a(static_cast<byte>(alpha)), 
		b(static_cast<byte>(blue)), 
		g(static_cast<byte>(green)),
		r(static_cast<byte>(red))
		{}

		Color::Color(float red, float green, float blue, float alpha) :
		a(static_cast<byte>(alpha * 255.0f)), 
		b(static_cast<byte>(blue * 255.0f)), 
		g(static_cast<byte>(green * 255.0f)),
		r(static_cast<byte>(red * 255.0f))
		{}

		Color(const Vector3& vec);
		Color(const Vector3& vec, byte alpha);
		Color(const Vector4& vec);

		Color& operator=(const Color& rhs);
		Color& operator=(const Vector3& rhs);
		Color& operator=(const Vector4& rhs);

		bool operator==(const Color& rhs);
		bool operator!=(const Color& rhs);

		inline float NormalizedR() const { return r / 255.0f; }
		inline float NormalizedG() const { return g / 255.0f; }
		inline float NormalizedB() const { return b / 255.0f; }
		inline float NormalizedA() const { return a / 255.0f; }

		inline Vector4 GetNormalizedVector() const { return Vector4(NormalizedR(), NormalizedG(), NormalizedB(), NormalizedA()); }

		inline String ToString() const
		{
			return "(" + String(static_cast<int>(r)) + ", " + String(static_cast<int>(g)) + 
				", " + String(static_cast<int>(b)) + ", " + String(static_cast<int>(a)) + ")";
		}
	};
}


#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::Color>()
	{
		return members(
			member("rgba", &Forge::Color::rgba)
		);
	}
}