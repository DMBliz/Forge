#pragma once

#include "Containers/String.h"

namespace Forge
{

	class Vector2i
	{
	public:
		int x;
		int y;

		Vector2i();
		Vector2i(int x, int y);
		Vector2i(const Vector2i& rhs);

		void Set(int x, int y) { this->x = x; this->y = y; }

		void operator=(const Vector2i& rhs);

		bool operator==(const Vector2i& rhs) const;
		bool operator!=(const Vector2i& rhs) const;

		Vector2i operator-() const;

		Vector2i operator+(const Vector2i& rhs) const;
		Vector2i operator-(const Vector2i& rhs) const;
		Vector2i operator/(const Vector2i& rhs) const;
		Vector2i operator/(int rhs) const;
		Vector2i operator*(const Vector2i& rhs) const;
		Vector2i operator*(int rhs) const;
		friend Vector2i operator*(int lhs, const Vector2i& rhs);

		Vector2i& operator+=(const Vector2i& rhs);
		Vector2i& operator-=(const Vector2i& rhs);
		Vector2i& operator*=(const Vector2i& rhs);
		Vector2i& operator*=(int rhs);
		Vector2i& operator/=(const Vector2i& rhs);
		Vector2i& operator/=(int rhs);
		
		float Length() const;
		
		String ToString() const;

	};

}


#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::Vector2i>()
	{
		return members(
			member("x", &Forge::Vector2i::x),
			member("y", &Forge::Vector2i::y)
		);
	}
}