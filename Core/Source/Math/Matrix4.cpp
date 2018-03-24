#include "Matrix4.h"
#include "Matrix3.h"
#include "Quaternion.h"
#include "Mathf.h"

namespace Forge 
{ 

	const Matrix4 Matrix4::Identity(1.0f);

	Matrix4::Matrix4()
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
		float m21, float m22, float m23, float m30, float m31, float m32, float m33)
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
		mels[3][0] = m30;
		mels[3][1] = m31;
		mels[3][2] = m32;
		mels[3][3] = m33;

	}

	Matrix4::Matrix4(float values[16])
	{
		memcpy(elements, values, 4 * 4 * sizeof(float));
	}

	Matrix4::Matrix4(float diagonal)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));

		mels[0][0] = diagonal;
		mels[1][1] = diagonal;
		mels[2][2] = diagonal;
		mels[3][3] = diagonal;
	}

	Matrix4::Matrix4(const Matrix4& other)
	{
		memcpy(elements, other.elements, 4 * 4 * sizeof(float));
	}

	Matrix4 Matrix4::Transponse() const
	{
		return Matrix4(mels[0][0], mels[1][0], mels[2][0], mels[3][0],
					   mels[0][1], mels[1][1], mels[2][1], mels[3][1],
					   mels[0][2], mels[1][2], mels[2][2], mels[3][2],
					   mels[0][3], mels[1][3], mels[2][3], mels[3][3]);
	}

	Matrix3 Matrix4::ToMatrix3() const
	{
		return Matrix3(
			mels[0][0], mels[0][1], mels[0][2],
			mels[1][0], mels[1][1], mels[1][2],
			mels[2][0], mels[2][1], mels[2][2]
		);
	}

	Matrix3 Matrix4::RotationMatrix() const
	{
		Vector3 invScale(
			1.0f / sqrtf(mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0]),
			1.0f / sqrtf(mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1]),
			1.0f / sqrtf(mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2])
		);

		return ToMatrix3().Scaled(invScale);
	}

	std::vector<float> Matrix4::Values() const
	{
		std::vector<float> vec(16);
		memcpy(vec.data(), elements, 16 * sizeof(float));
		return vec;
	}

	void Matrix4::Values(std::vector<float> values)
	{
		memcpy(elements, values.data(), 16 * sizeof(float));
	}

	void Matrix4::Decompose(Vector3& position, Quaternion& rotation, Vector3& scale)
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


	Matrix4 Matrix4::operator*(const Matrix4& rhs)
	{
		float temp[16];
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[e + x * 4] * rhs.elements[y + e * 4];
				}
				temp[y + x * 4] = sum;
			}
		}

		return Matrix4(temp);
	}

	Vector4 Matrix4::operator*(const Vector4& rhs)
	{
		return Vector4(
			mels[0][0] * rhs.x + mels[1][0] * rhs.y + mels[2][0] * rhs.z + mels[3][0] * rhs.w,
			mels[0][1] * rhs.x + mels[1][1] * rhs.y + mels[2][1] * rhs.z + mels[3][1] * rhs.w,
			mels[0][2] * rhs.x + mels[1][2] * rhs.y + mels[2][2] * rhs.z + mels[3][2] * rhs.w,
			mels[0][3] * rhs.x + mels[1][3] * rhs.y + mels[2][3] * rhs.z + mels[3][3] * rhs.w
		);
	}

	Vector3 Matrix4::operator*(const Vector3& rhs)
	{
		return Vector3(
			mels[0][0] * rhs.x + mels[1][0] * rhs.y + mels[2][0] * rhs.z + mels[3][0],
			mels[0][1] * rhs.x + mels[1][1] * rhs.y + mels[2][1] * rhs.z + mels[3][1],
			mels[0][2] * rhs.x + mels[1][2] * rhs.y + mels[2][2] * rhs.z + mels[3][2]
		);
	}

	Matrix4& Matrix4::operator*=(const Matrix4& other)
	{
		float temp[16];
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[e + x * 4] * other.elements[y + e * 4];
				}
				temp[y + x * 4] = sum;
			}
		}
		memcpy(elements, temp, 16 * sizeof(float));

		return *this;
	}

	void Matrix4::operator=(const Matrix4& rhs)
	{
		memcpy(elements, rhs.elements, 16 * sizeof(float));
	}

	void Matrix4::operator=(const Matrix4&& rhs)
	{
		memmove(elements, rhs.elements, 16 * sizeof(float));
	}

	bool Matrix4::operator==(const Matrix4& rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			if (elements[i] != rhs.elements[i])
				return false;
		}
		return true;
	}

	bool Matrix4::operator!=(const Matrix4& rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			if (elements[i] != rhs.elements[i])
				return true;
		}
		return false;
	}

	Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 res(1.0f);

		res.mels[0][0] = 2.0f / (right - left);
		res.mels[1][1] = 2.0f / (top - bottom);
		res.mels[2][2] = 2.0f / (near - far);

		res.mels[3][0] = (left + right) / (left - right);
		res.mels[3][1] = (bottom + top) / (bottom - top);
		res.mels[3][2] = (far + near) / (far - near);

		return res;
	}

	Matrix4 Matrix4::Perspective(float fov, float aspectRetio, float near, float far)
	{
		Matrix4 res(1.0f);

		float q = 1.0f / static_cast<float>(tan(fov * DEGTORAD_2));
		float a = q / aspectRetio;

		res.mels[0][0] = a;
		res.mels[1][1] = q;
		res.mels[2][2] = (near + far) / (near - far);
		res.mels[3][2] = -1.0f;
		res.mels[2][3] = (2.0f * near * far) / (near - far);

		return res;
	}

	Matrix4 Matrix4::Translate(const Vector3& translation)
	{
		Matrix4 res(1.0f);

		res.mels[0][3] = translation.x;
		res.mels[1][3] = translation.y;
		res.mels[2][3] = translation.z;

		return res;
	}

	Matrix4 Matrix4::Rotate(float angle, const Vector3& axis)
	{
		Matrix4 res(1.0f);

		float r = angle;
		float c = cos(r);
		float s = sin(r);
		float nc = 1.0f - c;

		res.mels[0][0] = axis.x * nc + c;
		res.mels[1][0] = axis.y * axis.x * nc + axis.z * s;
		res.mels[2][0] = axis.x * axis.z * nc - axis.y * s;

		res.mels[0][1] = axis.x * axis.y * nc - axis.z * s;
		res.mels[1][1] = axis.y * nc + c;
		res.mels[2][1] = axis.y * axis.z * nc + axis.x *s;

		res.mels[0][2] = axis.x * axis.z * nc + axis.y * s;
		res.mels[1][2] = axis.y * axis.z * nc - axis.x * s;
		res.mels[2][2] = axis.z * nc + c;

		return res;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		Matrix4 res(1.0f);

		res.mels[0][0] = scale.x;
		res.mels[1][1] = scale.y;
		res.mels[2][2] = scale.z;

		return res;
	}

    Vector3 Matrix4::GetTranslation() const
    {
        return Vector3(mels[0][3], mels[1][3], mels[2][3]);
    }

    Quaternion Matrix4::GetRotation() const
    {
        return Quaternion(RotationMatrix());
    }

    Vector3 Matrix4::GetScale() const
    {
        return Vector3(
            sqrtf(mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0]),
            sqrtf(mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1]),
            sqrtf(mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2])
        );
    }

	Matrix4::~Matrix4()
	{
	}
}
