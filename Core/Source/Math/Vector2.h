#pragma once
#include "Containers/String.h"

namespace Forge
{
	class Vector4;
	class Vector3;

	class Vector2
	{
	public:
		float x;
		float y;

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Down;

		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& vec);
		Vector2(const Vector3& vec);
		Vector2(const Vector4& vec);

		inline void Set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator+(const Vector2& rhs) const;

		Vector2 operator-(const Vector2& rhs) const;

		Vector2 operator*(const Vector2& rhs) const;
		Vector2 operator*(float rhs) const;
		friend Vector2 operator*(float lhs, Vector2 rhs);

		Vector2 operator/(const Vector2& rhs) const;
		Vector2 operator/(float rhs) const;

		Vector2& operator=(const Vector2& rhs);

		bool operator==(const Vector2& rhs) const;
		bool operator!=(const Vector2& rhs) const;

		Vector2 operator-() const;

		Vector2& operator+=(const Vector2& rhs);
		
		Vector2& operator-=(const Vector2& rhs);

		Vector2& operator*=(const Vector2& rhs);
		Vector2& operator*=(float rhs);
		
		Vector2& operator/=(const Vector2& rhs);
		Vector2& operator/=(float rhs);

		Vector2 Normalized() const;
		void Normalize();
		float Length() const;
		float LengthSquared() const;
		float Dot(const Vector2& rhs) const;
		float AbsDot(const Vector2& rhs) const;
		float ProjectOntoAxis(const Vector2& axis) const;
		float Angle(const Vector2& rhs) const;
		Vector2 Abs();
		Vector2 Lerp(const Vector2& rhs, float t) const;

		static Vector2 Lerp(const Vector2& lhs, const Vector2& rhs, const Vector2& t);
		static Vector2 Max(const Vector2& lhs, const Vector2& rhs);
		static Vector2 Min(const Vector2& lhs, const Vector2& rhs);
		static Vector2 Floor(const Vector2& vec);
		static Vector2 Round(const Vector2& vec);
		static Vector2 Ceil(const Vector2& vec);

		String ToString() const;
	};
}