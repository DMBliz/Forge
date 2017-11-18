#pragma once
#include "Containers/String.h"

namespace Forge
{
	class Vector4;
	class Vector3;


	class Color
	{
	public:
		union
		{
			unsigned int rgba;
			struct
			{
				unsigned char a;
				unsigned char b;
				unsigned char g;
				unsigned char r;
			};
		};

		Color::Color()
			: rgba(0x00000000)
		{}

		Color::Color(unsigned int color)
			: rgba(color)
		{}

		Color::Color(const Color& color)
			: rgba(color.rgba)
		{}

		Color::Color(int red, int green, int blue)
			: r(red), g(green), b(blue), a(255)
		{}

		Color::Color(float red, float green, float blue)
			: r(red * 255.0f), g(green * 255.0f), b(blue * 255.0f), a(255)
		{}

		Color::Color(int red, int green, int blue, int alpha)
			: r(red), g(green), b(blue), a(alpha)
		{}

		Color::Color(float red, float green, float blue, float alpha)
			: r(red * 255.0f), g(green * 255.0f), b(blue * 255.0f), a(alpha * 255.0f)
		{}

		Color(const Vector3& vec);
		Color(const Vector3& vec, unsigned char alpha);
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

		inline String ToString() const
		{
			return "(" + String(static_cast<int>(r)) + ", " + String(static_cast<int>(g)) + 
				", " + String(static_cast<int>(b)) + ", " + String(static_cast<int>(a)) + ")";
		}
	};
}
