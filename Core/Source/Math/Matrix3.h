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
			Vector3 vectors[3];
		};

		Matrix3();
		Matrix3(const Matrix3& matrix);
		Matrix3(const Vector3& vector);
		Matrix3(float values[9]);

		bool operator==(const Matrix3& rhs) const;
		bool operator!=(const Matrix3& rhs) const;

		Matrix3& operator=(const Matrix3& rhs);
		Matrix3 operator*(const Matrix3& rhs) const;
		Vector3 operator*(const Vector3& rhs) const;
		Matrix3 operator*(float rhs) const;
		Matrix3 operator+(const Matrix3& rhs) const;
		Matrix3 operator-(const Matrix3& rhs) const;

		void SetScale(const Vector3& scale);
		void SetScale(float scale);
		Vector3 Scale() const;
		Matrix3 Inverse() const;
		Matrix3 Transponse() const;

		String ToString() const;

		
	};

}
