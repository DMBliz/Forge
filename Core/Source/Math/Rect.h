#pragma once

#include "Mathf.h"
#include "Containers/String.h"

namespace Forge
{
	class Rect
	{
	public:
		Vector2 min;
		Vector2 max;
		
		static const Rect Full;
		static const Rect Positive;
		static const Rect Zero;

		Rect();
		Rect(const Vector2& min, const Vector2& max);
		Rect(float left, float top, float right, float bottom);
		Rect(const Vector4& vector);
		Rect(const Rect& rect);

		Rect& operator=(const Rect& rhs);
		bool operator==(const Rect& rhs) const;
		bool operator!=(const Rect& rhs) const;

		void Set(const Rect& rect);
		void Set(const Vector2& min, const Vector2& max);
		
		Vector2 Center() const;
		Vector2 Size() const;

		Vector4 ToVector4() const;
		String ToString() const;

	};
}
