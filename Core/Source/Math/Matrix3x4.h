#pragma once
#include <vector>

namespace Forge
{
	class Vector4;
	class Quaternion;
	class Vector3;
	class Matrix4;
	class Matrix3;

	class Matrix3x4
	{
	public:

		union
		{
			float elements[12];
			float mels[3][4];
		};

		Matrix3x4();
		Matrix3x4(const Matrix3x4& matrix);
		Matrix3x4(const Matrix3& matrix);
		Matrix3x4(const Matrix4& matrix);
		Matrix3x4(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12, float m13,
				  float m20, float m21, float m22, float m23);
		Matrix3x4(const float* values);
		Matrix3x4(const Vector3& positon, const Quaternion& rotation, float scale);
		Matrix3x4(const Vector3& positon, const Quaternion& rotation, Vector3 scale);
		~Matrix3x4();

		std::vector<float> Values() const;
		void Values(std::vector<float> values);

		Matrix3x4& operator=(const Matrix3x4& rhs);
		Matrix3x4& operator=(const Matrix3& rhs);
		Matrix3x4& operator=(const Matrix4& rhs);

		bool operator==(const Matrix3x4& rhs);
		bool operator!=(const Matrix3x4& rhs);

		Matrix3x4 operator*(const float rhs);
		Vector3 operator*(const Vector3& rhs);
		Vector3 operator*(const Vector4& rhs);
		Matrix3x4 operator*(const Matrix3x4& rhs);
		Matrix4 operator*(const Matrix4& rhs);

		Matrix3x4 operator+(const Matrix3x4& rhs);
		Matrix3x4 operator-(const Matrix3x4& rhs);


		void SetPosition(const Vector3& position);
		void SetRotation(const Matrix3& rotation);
		void SetScale(float scale);
		void SetScale(const Vector3 &scale);

		Matrix3 ToMatrix3() const;
		Matrix4 ToMatrix4() const;

		Matrix3 RotationMatrix() const;

		Vector3 Translation() const;
		Quaternion Rotation() const;
		Vector3 Scale() const;

		Vector3 SignedScale(const Matrix3& rotation) const;

		void Decompose(Vector3& position, Quaternion& rotation, Vector3& scale) const;

		Matrix3x4 Inverse() const;


	};

}


#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::Matrix3x4>()
	{
		return members(
			member("elements", &Forge::Matrix3x4::Values, &Forge::Matrix3x4::Values)
		);
	}
}