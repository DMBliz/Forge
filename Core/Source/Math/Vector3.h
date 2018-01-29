#pragma once
#include <ostream>
#include "Containers/String.h"

namespace Forge
{ 
	class Vector4;
	class Vector2;

	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Back;

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector2& vec);
		Vector3(const Vector2& vec, float z);
		Vector3(const Vector3& vec);
		Vector3(const Vector4& vec);

		inline void SetPosition(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

		Vector3 operator+(const Vector3& rhs) const;

		Vector3 operator-(const Vector3& rhs) const;

		Vector3 operator*(const Vector3& rhs) const;
		Vector3 operator*(float rhs) const;
		friend Vector3 operator*(float lhs, Vector3 rhs);

		Vector3 operator/(const Vector3& rhs) const;
		Vector3 operator/(float rhs) const;

		Vector3& operator=(const Vector3& rhs);

		bool operator==(const Vector3& rhs) const;
		bool operator!=(const Vector3& rhs) const;

		Vector3 operator-() const;

		Vector3& operator+=(const Vector3& rhs);

		Vector3& operator-=(const Vector3& rhs);

		Vector3& operator*=(const Vector3& rhs);
		Vector3& operator*=(float rhs);

		Vector3& operator/=(const Vector3& rhs);
		Vector3& operator/=(float rhs);

		Vector3 Normalized() const;
		void Normalize();
		float Length() const;
		float LengthSquared() const;
		float Dot(const Vector3& rhs) const;
		float AbsDot(const Vector3& rhs) const;
		Vector3 Cross(const Vector3& rhs) const;
		Vector3 Orthogonalize(const Vector3& axis) const;
		float ProjectOntoAxis(const Vector3& axis) const;
		float Angle(const Vector3& rhs) const;
		Vector3 Abs();
		Vector3 Lerp(const Vector3& rhs, float t) const;

		static friend Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, const Vector3& t);
		static friend Vector3 Max(const Vector3& lhs, const Vector3& rhs);
		static friend Vector3 Min(const Vector3& lhs, const Vector3& rhs);
		static friend Vector3 Floor(const Vector3& vec);
		static friend Vector3 Round(const Vector3& vec);
		static friend Vector3 Ceil(const Vector3& vec);

		String ToString() const;
	};
}


#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::Vector3>()
	{
		return members(
			member("x", &Forge::Vector3::x),
			member("y", &Forge::Vector3::y),
			member("z", &Forge::Vector3::z)
		);
	}
}