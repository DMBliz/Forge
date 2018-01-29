#pragma once
#include "Vector4.h"

//TODO: refactor this
namespace Forge 
{
	class Quaternion;
	class Vector3;
	class Matrix3;

	class Matrix4
	{
	public:
		union 
		{
			float elements[4 * 4];
			float mels[4][4];
		};

		Matrix4();
		Matrix4(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33);
		Matrix4(float values[16]);
		Matrix4(float diagonal);
		Matrix4(const Matrix4& other);


		Matrix4 Transponse();
		Matrix3 ToMatrix3();
		Matrix3 RotationMatrix();

		std::vector<float> Values() const;
		void Values(std::vector<float> values);

		void Decompose(Vector3& position, Quaternion& rotation, Vector3& scale);

		static const Matrix4 Identity;
		//Matrix4& Invert();

		static Matrix4 Orthographic(float lhs, float rhs, float bottom, float top, float near, float far);
		static Matrix4 Perspective(float fov, float aspectRetio, float near, float far);

		static Matrix4 Translate(const Vector3& translation);
		static Matrix4 Rotate(float angle, const Vector3& axis);
		static Matrix4 Scale(const Vector3& scale);

		Matrix4 operator*(const Matrix4& rhs);
		Vector4 operator*(const Vector4& rhs);
		Vector3 operator*(const Vector3& rhs);
		Matrix4& operator*=(const Matrix4& rhs);

		void operator=(const Matrix4& rhs);
		void operator=(const Matrix4&& rhs);

		bool operator==(const Matrix4& rhs);
		bool operator!=(const Matrix4& rhs);


		~Matrix4();
	};
}

#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::Matrix4>()
	{
		return members(
			member("elements", &Forge::Matrix4::Values, &Forge::Matrix4::Values)
		);
	}
}