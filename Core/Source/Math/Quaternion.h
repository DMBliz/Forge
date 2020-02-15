#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include "Containers/String.h"

namespace Forge
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		static const Quaternion Identity;

		Quaternion();
		Quaternion(float w, float x, float y, float z);
		Quaternion(const Quaternion& quat);
		Quaternion(float angle, const Vector3& axis);
		Quaternion(float x, float y, float z);
		Quaternion(const Vector3& start, const Vector3& end);
		Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		Quaternion(const Matrix3& matrix);

		bool operator==(const Quaternion& rhs) const;
		bool operator!=(const Quaternion& rhs) const; 

		Quaternion operator-() const;

		Quaternion& operator=(const Quaternion& rhs);
		Quaternion& operator+=(const Quaternion& rhs);
		Quaternion& operator-=(const Quaternion& rhs);
		Quaternion& operator*=(const Quaternion& rhs);
		Quaternion& operator*=(float rhs);

		Quaternion operator+(const Quaternion& rhs) const;
		Quaternion operator-(const Quaternion& rhs) const;
		Quaternion operator*(const Quaternion& rhs) const;
		Vector3 operator*(const Vector3& rhs) const;
		Quaternion operator*(float rhs) const;
		friend Quaternion operator*(float lhs, const Quaternion& rhs);

		void FromAngleAxis(float angle, const Vector3& axis);
		void FromEulerAngles(float x, float y, float z);
		void FromEulerAngles(const Vector3& vector);
		void FromRotationTo(const Vector3& start, const Vector3& end);
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		void FromRotationMatrix(const Matrix3& matrix);
		void FromLookRotation(const Vector3& direction, const Vector3& up = Vector3::Up);

		void Nomalize();
		Quaternion Normalized() const;
		Quaternion Inverse() const;
		float LengthSquared() const;
		float Dot(const Quaternion& rhs) const;

		Quaternion Conjugate() const;
		Vector3 EulerAngles() const;
		Vector3 Axis() const;
		float Angle() const;
		Matrix3 RotationMatrix() const;
		Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
		Quaternion Slerp(const Quaternion& rhs, float t) const;
		Quaternion Nlerp(const Quaternion& rhs, float t, bool shortPath = false) const;

        static Vector3 Rotate(const Quaternion& quaternion, const Vector3& vector);

		String ToString() const;

		static Quaternion FromEuler(const Vector3& rotation);
		static Quaternion FromEuler(float x, float y, float z);
		static Vector3 ToEuler(const Quaternion& rotation);
	};
}