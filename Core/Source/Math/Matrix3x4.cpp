#include "Matrix3x4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include <cstring>
#include <math.h>
namespace Forge
{

	Matrix3x4::Matrix3x4()
	{
		memset(elements, 0, 12 * sizeof(float));
		mels[0][0] = 1;
		mels[1][1] = 1;
		mels[2][2] = 1;
	}

	Matrix3x4::Matrix3x4(const Matrix3x4& matrix)
	{
		memcpy(elements, matrix.elements, 12 * sizeof(float));
	}

	Matrix3x4::Matrix3x4(const Matrix3& matrix)
	{
		mels[0][0] = matrix.mels[0][0];
		mels[0][1] = matrix.mels[0][1];
		mels[0][2] = matrix.mels[0][2];
		mels[0][3] = 0;
		mels[1][0] = matrix.mels[1][0];
		mels[1][1] = matrix.mels[1][1];
		mels[1][2] = matrix.mels[1][2];
		mels[1][3] = 0;
		mels[2][0] = matrix.mels[2][0];
		mels[2][1] = matrix.mels[2][1];
		mels[2][2] = matrix.mels[2][2];
		mels[2][3] = 0;
	}

	Matrix3x4::Matrix3x4(const Matrix4& matrix)
	{
		mels[0][0] = matrix.mels[0][0];
		mels[0][1] = matrix.mels[0][1];
		mels[0][2] = matrix.mels[0][2];
		mels[0][3] = matrix.mels[0][3];
		mels[1][0] = matrix.mels[1][0];
		mels[1][1] = matrix.mels[1][1];
		mels[1][2] = matrix.mels[1][2];
		mels[1][3] = matrix.mels[1][3];
		mels[2][0] = matrix.mels[2][0];
		mels[2][1] = matrix.mels[2][1];
		mels[2][2] = matrix.mels[2][2];
		mels[2][3] = matrix.mels[2][3];
	}

	Matrix3x4::Matrix3x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
		float m21, float m22, float m23)
	{
		mels[0][0] = m00;
		mels[0][1] = m01;
		mels[0][2] = m02;
		mels[0][3] = m03;
		mels[1][0] = m10;
		mels[1][1] = m11;
		mels[1][2] = m12;
		mels[1][3] = m13;
		mels[2][0] = m20;
		mels[2][1] = m21;
		mels[2][2] = m22;
		mels[2][3] = m23;
	}

	Matrix3x4::Matrix3x4(const float* values)
	{
		memcpy(elements, values, 12);
	}

	Matrix3x4::Matrix3x4(const Vector3& positon, const Quaternion& rotation, float scale)
	{
		SetRotation(rotation.RotationMatrix() * scale);
		SetPosition(positon);
	}

	Matrix3x4::Matrix3x4(const Vector3& positon, const Quaternion& rotation, Vector3 scale)
	{
		SetRotation(rotation.RotationMatrix().Scaled(scale));
		SetPosition(positon);
	}

	Matrix3x4::~Matrix3x4()
	{}

	std::vector<float> Matrix3x4::Values() const
	{
		std::vector<float> vec(12);
		memcpy(vec.data(), elements, 12 * sizeof(float));
		return vec;
	}

	void Matrix3x4::Values(std::vector<float> values)
	{
		memcpy(elements, values.data(), 12 * sizeof(float));
	}

	Matrix3x4& Matrix3x4::operator=(const Matrix3x4& rhs)
	{
		memcpy(elements, rhs.elements, 12 * sizeof(float));
		return *this;
	}

	Matrix3x4& Matrix3x4::operator=(const Matrix3& rhs)
	{
		mels[0][0] = rhs.mels[0][0];
		mels[0][1] = rhs.mels[0][1];
		mels[0][2] = rhs.mels[0][2];
		mels[0][3] = 0;
		mels[1][0] = rhs.mels[1][0];
		mels[1][1] = rhs.mels[1][1];
		mels[1][2] = rhs.mels[1][2];
		mels[1][3] = 0;
		mels[2][0] = rhs.mels[2][0];
		mels[2][1] = rhs.mels[2][1];
		mels[2][2] = rhs.mels[2][2];
		mels[2][3] = 0;

		return *this;
	}

	Matrix3x4& Matrix3x4::operator=(const Matrix4& rhs)
	{
		mels[0][0] = rhs.mels[0][0];
		mels[0][1] = rhs.mels[0][1];
		mels[0][2] = rhs.mels[0][2];
		mels[0][3] = rhs.mels[0][3];
		mels[1][0] = rhs.mels[1][0];
		mels[1][1] = rhs.mels[1][1];
		mels[1][2] = rhs.mels[1][2];
		mels[1][3] = rhs.mels[1][3];
		mels[2][0] = rhs.mels[2][0];
		mels[2][1] = rhs.mels[2][1];
		mels[2][2] = rhs.mels[2][2];
		mels[2][3] = rhs.mels[2][3];

		return *this;
	}

	bool Matrix3x4::operator==(const Matrix3x4& rhs)
	{
		for (int i = 0; i < 12; i++)
		{
			if (elements[i] != rhs.elements[i])
				return false;
		}
		return true;
	}

	bool Matrix3x4::operator!=(const Matrix3x4& rhs)
	{
		for (int i = 0; i < 12; i++)
		{
			if (elements[i] != rhs.elements[i])
				return true;
		}
		return false;
	}

	Matrix3x4 Matrix3x4::operator*(const float rhs)
	{
		return Matrix3x4(
			mels[0][0] * rhs,
			mels[0][1] * rhs,
			mels[0][2] * rhs,
			mels[0][3] * rhs,
			mels[1][0] * rhs,
			mels[1][1] * rhs,
			mels[1][2] * rhs,
			mels[1][3] * rhs,
			mels[2][0] * rhs,
			mels[2][1] * rhs,
			mels[2][2] * rhs,
			mels[2][3] * rhs
		);
	}

	Vector3 Matrix3x4::operator*(const Vector3& rhs)
	{
		return Vector3(
			mels[0][0] * rhs.x + mels[0][1] * rhs.y + mels[0][2] * rhs.z + mels[0][3],
			mels[1][0] * rhs.x + mels[1][1] * rhs.y + mels[1][2] * rhs.z + mels[1][3],
			mels[2][0] * rhs.x + mels[2][1] * rhs.y + mels[2][2] * rhs.z + mels[2][3]
		);
	}

	Vector3 Matrix3x4::operator*(const Vector4& rhs)
	{
		return Vector3(
			mels[0][0] * rhs.x + mels[0][1] * rhs.y + mels[0][2] * rhs.z + mels[0][3] * rhs.w,
			mels[1][0] * rhs.x + mels[1][1] * rhs.y + mels[1][2] * rhs.z + mels[1][3] * rhs.w,
			mels[2][0] * rhs.x + mels[2][1] * rhs.y + mels[2][2] * rhs.z + mels[2][3] * rhs.w
		);
	}

	Matrix3x4 Matrix3x4::operator*(const Matrix3x4& rhs)
	{
		return Matrix3x4(
			mels[0][0] * rhs.mels[0][0] + mels[0][1] * rhs.mels[1][0] + mels[0][2] * rhs.mels[2][0],
			mels[0][0] * rhs.mels[0][1] + mels[0][1] * rhs.mels[1][1] + mels[0][2] * rhs.mels[2][1],
			mels[0][0] * rhs.mels[0][2] + mels[0][1] * rhs.mels[1][2] + mels[0][2] * rhs.mels[2][2],
			mels[0][0] * rhs.mels[0][3] + mels[0][1] * rhs.mels[1][3] + mels[0][2] * rhs.mels[2][3] + mels[0][3],
			mels[1][0] * rhs.mels[0][0] + mels[1][1] * rhs.mels[1][0] + mels[1][2] * rhs.mels[2][0],
			mels[1][0] * rhs.mels[0][1] + mels[1][1] * rhs.mels[1][1] + mels[1][2] * rhs.mels[2][1],
			mels[1][0] * rhs.mels[0][2] + mels[1][1] * rhs.mels[1][2] + mels[1][2] * rhs.mels[2][2],
			mels[1][0] * rhs.mels[0][3] + mels[1][1] * rhs.mels[1][3] + mels[1][2] * rhs.mels[2][3] + mels[1][3],
			mels[2][0] * rhs.mels[0][0] + mels[2][1] * rhs.mels[1][0] + mels[2][2] * rhs.mels[2][0],
			mels[2][0] * rhs.mels[0][1] + mels[2][1] * rhs.mels[1][1] + mels[2][2] * rhs.mels[2][1],
			mels[2][0] * rhs.mels[0][2] + mels[2][1] * rhs.mels[1][2] + mels[2][2] * rhs.mels[2][2],
			mels[2][0] * rhs.mels[0][3] + mels[2][1] * rhs.mels[1][3] + mels[2][2] * rhs.mels[2][3] + mels[2][3]
		);
	}

	Matrix4 Matrix3x4::operator*(const Matrix4& rhs)
	{
		return Matrix4(
			mels[0][0] * rhs.mels[0][0] + mels[0][1] * rhs.mels[1][0] + mels[0][2] * rhs.mels[2][0] + mels[0][3] * rhs.mels[3][0],
			mels[0][0] * rhs.mels[0][1] + mels[0][1] * rhs.mels[1][1] + mels[0][2] * rhs.mels[2][1] + mels[0][3] * rhs.mels[3][1],
			mels[0][0] * rhs.mels[0][2] + mels[0][1] * rhs.mels[1][2] + mels[0][2] * rhs.mels[2][2] + mels[0][3] * rhs.mels[3][2],
			mels[0][0] * rhs.mels[0][3] + mels[0][1] * rhs.mels[1][3] + mels[0][2] * rhs.mels[2][3] + mels[0][3] * rhs.mels[3][3],
			mels[1][0] * rhs.mels[0][0] + mels[1][1] * rhs.mels[1][0] + mels[1][2] * rhs.mels[2][0] + mels[1][3] * rhs.mels[3][0],
			mels[1][0] * rhs.mels[0][1] + mels[1][1] * rhs.mels[1][1] + mels[1][2] * rhs.mels[2][1] + mels[1][3] * rhs.mels[3][1],
			mels[1][0] * rhs.mels[0][2] + mels[1][1] * rhs.mels[1][2] + mels[1][2] * rhs.mels[2][2] + mels[1][3] * rhs.mels[3][2],
			mels[1][0] * rhs.mels[0][3] + mels[1][1] * rhs.mels[1][3] + mels[1][2] * rhs.mels[2][3] + mels[1][3] * rhs.mels[3][3],
			mels[2][0] * rhs.mels[0][0] + mels[2][1] * rhs.mels[1][0] + mels[2][2] * rhs.mels[2][0] + mels[2][3] * rhs.mels[3][0],
			mels[2][0] * rhs.mels[0][1] + mels[2][1] * rhs.mels[1][1] + mels[2][2] * rhs.mels[2][1] + mels[2][3] * rhs.mels[3][1],
			mels[2][0] * rhs.mels[0][2] + mels[2][1] * rhs.mels[1][2] + mels[2][2] * rhs.mels[2][2] + mels[2][3] * rhs.mels[3][2],
			mels[2][0] * rhs.mels[0][3] + mels[2][1] * rhs.mels[1][3] + mels[2][2] * rhs.mels[2][3] + mels[2][3] * rhs.mels[3][3],
			rhs.mels[3][0],
			rhs.mels[3][1],
			rhs.mels[3][2],
			rhs.mels[3][3]
		);
	}

	Matrix3x4 Matrix3x4::operator+(const Matrix3x4& rhs)
	{
		return Matrix3x4(
			mels[0][0] + rhs.mels[0][0],
			mels[0][1] + rhs.mels[0][1],
			mels[0][2] + rhs.mels[0][2],
			mels[0][3] + rhs.mels[0][3],
			mels[1][0] + rhs.mels[1][0],
			mels[1][1] + rhs.mels[1][1],
			mels[1][2] + rhs.mels[1][2],
			mels[1][3] + rhs.mels[1][3],
			mels[2][0] + rhs.mels[2][0],
			mels[2][1] + rhs.mels[2][1],
			mels[2][2] + rhs.mels[2][2],
			mels[2][3] + rhs.mels[2][3]
		);
	}

	Matrix3x4 Matrix3x4::operator-(const Matrix3x4& rhs)
	{
		return Matrix3x4(
			mels[0][0] - rhs.mels[0][0],
			mels[0][1] - rhs.mels[0][1],
			mels[0][2] - rhs.mels[0][2],
			mels[0][3] - rhs.mels[0][3],
			mels[1][0] - rhs.mels[1][0],
			mels[1][1] - rhs.mels[1][1],
			mels[1][2] - rhs.mels[1][2],
			mels[1][3] - rhs.mels[1][3],
			mels[2][0] - rhs.mels[2][0],
			mels[2][1] - rhs.mels[2][1],
			mels[2][2] - rhs.mels[2][2],
			mels[2][3] - rhs.mels[2][3]
		);
	}

	void Matrix3x4::SetPosition(const Vector3& position)
	{
		mels[0][3] = position.x;
		mels[1][3] = position.y;
		mels[2][3] = position.z;
	}

	void Matrix3x4::SetRotation(const Matrix3& rotation)
	{
		mels[0][0] = rotation.mels[0][0];
		mels[0][1] = rotation.mels[0][1];
		mels[0][2] = rotation.mels[0][2];

		mels[1][0] = rotation.mels[1][0];
		mels[1][1] = rotation.mels[1][1];
		mels[1][2] = rotation.mels[1][2];

		mels[2][0] = rotation.mels[2][0];
		mels[2][1] = rotation.mels[2][1];
		mels[2][2] = rotation.mels[2][2];
	}

	void Matrix3x4::SetScale(float scale)
	{
		mels[0][0] = scale;
		mels[1][1] = scale;
		mels[2][2] = scale;
	}

	void Matrix3x4::SetScale(const Vector3& scale)
	{
		mels[0][0] = scale.x;
		mels[1][1] = scale.y;
		mels[2][2] = scale.z;
	}

	Matrix3 Matrix3x4::ToMatrix3() const
	{
		return Matrix3(
			mels[0][0], mels[0][1], mels[0][2],
			mels[1][0], mels[1][1], mels[1][2],
			mels[2][0], mels[2][1], mels[2][2]
		);
	}

	Matrix4 Matrix3x4::ToMatrix4() const
	{
		return Matrix4(
			mels[0][0], mels[0][1], mels[0][2], mels[0][3],
			mels[1][0], mels[1][1], mels[1][2], mels[1][3],
			mels[2][0], mels[2][1], mels[2][2], mels[2][3],
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix3 Matrix3x4::RotationMatrix() const
	{
		Vector3 invScale(
			1.0f / sqrtf(mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0]),
			1.0f / sqrtf(mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1]),
			1.0f / sqrtf(mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2])
		);

		return ToMatrix3().Scaled(invScale);
	}

	Vector3 Matrix3x4::Translation() const
	{
		return Vector3(mels[0][3], mels[1][3], mels[2][3]);
	}

	Quaternion Matrix3x4::Rotation() const
	{
		return Quaternion(RotationMatrix());
	}

	Vector3 Matrix3x4::Scale() const
	{
		return Vector3(
			sqrtf(mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0]),
			sqrtf(mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1]),
			sqrtf(mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2])
		);
	}

	Vector3 Matrix3x4::SignedScale(const Matrix3& rotation) const
	{
		return Vector3(
			rotation.mels[0][0] * mels[0][0] + rotation.mels[1][0] * mels[1][0] + rotation.mels[2][0] * mels[2][0],
			rotation.mels[0][1] * mels[0][1] + rotation.mels[1][1] * mels[1][1] + rotation.mels[2][1] * mels[2][1],
			rotation.mels[0][2] * mels[0][2] + rotation.mels[1][2] * mels[1][2] + rotation.mels[2][2] * mels[2][2]
		);
	}

	void Matrix3x4::Decompose(Vector3& position, Quaternion& rotation, Vector3& scale) const
	{
		position.x = mels[0][3];
		position.y = mels[1][3];
		position.z = mels[2][3];

		scale.x = sqrtf(mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0]);
		scale.y = sqrtf(mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1]);
		scale.z = sqrtf(mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2]);

		Vector3 invScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);

		rotation = Quaternion(ToMatrix3().Scaled(invScale));
	}

	Matrix3x4 Matrix3x4::Inverse() const
	{
		float det = mels[0][0] * mels[1][1] * mels[2][2] +
			mels[1][0] * mels[2][1] * mels[0][2] +
			mels[2][0] * mels[0][1] * mels[1][2] -
			mels[2][0] * mels[1][1] * mels[0][2] -
			mels[1][0] * mels[0][1] * mels[2][2] -
			mels[0][0] * mels[2][1] * mels[1][2];

		float invDet = 1.0f / det;
		Matrix3x4 ret;

		ret.mels[0][0] = (mels[1][1] * mels[2][2] - mels[2][1] * mels[1][2]) * invDet;
		ret.mels[0][1] = -(mels[0][1] * mels[2][2] - mels[2][1] * mels[0][2]) * invDet;
		ret.mels[0][2] = (mels[0][1] * mels[1][2] - mels[1][1] * mels[0][2]) * invDet;
		ret.mels[0][3] = -(mels[0][3] * ret.mels[0][0] + mels[1][3] * ret.mels[0][1] + mels[2][3] * ret.mels[0][2]);
		ret.mels[1][0] = -(mels[1][0] * mels[2][2] - mels[2][0] * mels[1][2]) * invDet;
		ret.mels[1][1] = (mels[0][0] * mels[2][2] - mels[2][0] * mels[0][2]) * invDet;
		ret.mels[1][2] = -(mels[0][0] * mels[1][2] - mels[1][0] * mels[0][2]) * invDet;
		ret.mels[1][3] = -(mels[0][3] *	ret.mels[1][0] + mels[1][3] * ret.mels[1][1] + mels[2][3] * ret.mels[1][2]);
		ret.mels[2][0] = (mels[1][0] * mels[2][1] - mels[2][0] * mels[1][1]) * invDet;
		ret.mels[2][1] = -(mels[0][0] *	mels[2][1] - mels[2][0] * mels[0][1]) * invDet;
		ret.mels[2][2] = (mels[0][0] * mels[1][1] - mels[1][0] * mels[0][1]) * invDet;
		ret.mels[2][3] = -(mels[0][3] * ret.mels[2][0] + mels[1][3] * ret.mels[2][1] + mels[2][3] * ret.mels[2][2]);

		return ret;
	}
}
