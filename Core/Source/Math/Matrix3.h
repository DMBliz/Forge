#pragma once
#include "Containers/String.h"
#include "Vector3.h"

namespace Forge
{
	class Matrix3
	{
	public:
		union
		{
			float elements[9];
			float mels[3][3];
		};

		Matrix3();
		Matrix3(float m00, float m01, float m02,
				float m10, float m11, float m12,
				float m20, float m21, float m22);

		Matrix3(const Matrix3& matrix);
		Matrix3(const Vector3& vector);
		Matrix3(float values[9]);


		std::vector<float> Values() const;
		void Values(std::vector<float> values);

		bool operator==(const Matrix3& rhs) const;
		bool operator!=(const Matrix3& rhs) const;

		Matrix3& operator=(const Matrix3& rhs);
		Matrix3 operator*(const Matrix3& rhs) const;
		Vector3 operator*(const Vector3& rhs) const;
		Matrix3 operator*(float rhs) const;
		Matrix3 operator+(const Matrix3& rhs) const;
		Matrix3 operator-(const Matrix3& rhs) const;

		Matrix3 Scaled(const Vector3& scale);
		void SetScale(const Vector3& scale);
		void SetScale(float scale);
		Vector3 Scale() const;
		Matrix3 Inverse() const;
		Matrix3 Transponse() const;

		String ToString() const;

		
	};

}