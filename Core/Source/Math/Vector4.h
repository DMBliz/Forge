#pragma once
#include <ostream>
#include "Containers/String.h"

namespace Forge
{
	class Vector3;
	class Vector2;

	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		static const Vector4 Zero;
		static const Vector4 One;

		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector2& vec);
		Vector4(const Vector2& vec, float z, float w);
		Vector4(const Vector3& vec);
		Vector4(const Vector3& vec, float w);
		Vector4(const Vector4& vec);

		inline void SetPosition(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }

		Vector4 operator+(const Vector4& rhs) const;

		Vector4 operator-(const Vector4& rhs) const;

		Vector4 operator*(const Vector4& rhs) const;
		Vector4 operator*(float rhs) const;
		friend Vector4 operator*(float lhs, Vector4 rhs);

		Vector4 operator/(const Vector4& rhs) const;
		Vector4 operator/(float rhs) const;

		Vector4& operator=(const Vector4& rhs);

		bool operator==(const Vector4& rhs) const;
		bool operator!=(const Vector4& rhs) const;

		Vector4 operator-() const;

		Vector4& operator+=(const Vector4& rhs);

		Vector4& operator-=(const Vector4& rhs);

		Vector4& operator*=(const Vector4& rhs);
		Vector4& operator*=(float rhs);

		Vector4& operator/=(const Vector4& rhs);
		Vector4& operator/=(float rhs);

		float Dot(const Vector4& rhs) const;
		float AbsDot(const Vector4& rhs) const;
		float ProjectOntoAxis(const Vector3& axis) const;
		Vector4 Abs() const;
		Vector4 Lerp(const Vector4& rhs, float t) const;

		static Vector4 Lerp(const Vector4& lhs, const Vector4& rhs, const Vector4& t);
		static Vector4 Max(const Vector4& lhs, const Vector4& rhs);
		static Vector4 Min(const Vector4& lhs, const Vector4& rhs);
		static Vector4 Floor(const Vector4& vec);
		static Vector4 Round(const Vector4& vec);
		static Vector4 Ceil(const Vector4& vec);

		String ToString() const;
	};
}