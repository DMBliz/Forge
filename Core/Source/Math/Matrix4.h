#pragma once
#include "Vector4.h"

//TODO: refactor this
namespace Forge 
{
	class Vector3;

	class Matrix4
	{
	public:
		union 
		{
			float elements[4 * 4];
			Vector4 vectors[4];
		};

		Matrix4();
		Matrix4(float values[16]);
		Matrix4(float diagonal);
		Matrix4(Matrix4& other);

		static const Matrix4 Identity;

		Matrix4& Multiply(const Matrix4& other);
		Vector4 Multiply(const Vector4& other) const;
		Vector3 Multiply(const Vector3& other) const;
		//Matrix4& Invert();

		static Matrix4 Orthographic(float lhs, float rhs, float bottom, float top, float near, float far);
		static Matrix4 Perspective(float fov, float aspectRetio, float near, float far);

		static Matrix4 Translation(const Vector3& translation);
		static Matrix4 Rotation(float angle, const Vector3& axis);
		static Matrix4 Scale(const Vector3& scale);

		friend Matrix4 operator*(Matrix4 lhs, const Matrix4& rhs);
		friend Vector4 operator*(const Matrix4& lhs, const Vector4& rhs);
		friend Vector3 operator*(const Matrix4& lhs, const Vector3& rhs);
		Matrix4& operator*=(const Matrix4& rhs);

		bool operator==(const Matrix4& rhs);
		bool operator!=(const Matrix4& rhs);


		~Matrix4();
	};
}
