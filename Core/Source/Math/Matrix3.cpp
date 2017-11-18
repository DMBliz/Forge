#include "Matrix3.h"

namespace Forge
{

	Matrix3::Matrix3()
	{
		memset(elements, 0, 3 * 3 * sizeof(float));
	}

	Matrix3::Matrix3(const Matrix3& matrix)
	{
		memcpy(elements, matrix.elements, 3 * 3 * sizeof(float));
	}

	Matrix3::Matrix3(const Vector3& vector)
	{
		memset(elements, 0, 3 * 3 * sizeof(float));
		SetScale(vector);
	}

	Matrix3::Matrix3(float values[9])
	{
		memcpy(elements, values, 3 * 3 * sizeof(float));
	}

	bool Matrix3::operator==(const Matrix3& rhs) const
	{
		for (int i = 0; i < 9; i++)
		{
			if (elements[i] != rhs.elements[i])
				return false;
		}
		return true;
	}

	bool Matrix3::operator!=(const Matrix3& rhs) const
	{
		for (int i = 0; i < 9; i++)
		{
			if (elements[i] != rhs.elements[i])
				return true;
		}
		return false;
	}

	Matrix3& Matrix3::operator=(const Matrix3& rhs)
	{
		memcpy(elements, rhs.elements, 3 * 3 * sizeof(float));

		return *this;
	}

	Matrix3 Matrix3::operator*(const Matrix3& rhs) const
	{
		float temp[9];

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 3; e++)
				{
					sum += elements[e + x * 3] * rhs.elements[y + e * 3];
				}
				temp[y + x * 3] = sum;
			}
		}

		return Matrix3(temp);
	}

	Vector3 Matrix3::operator*(const Vector3& rhs) const
	{
		return Vector3(
			mels[0][0] * rhs.x + mels[0][1] * rhs.y + mels[0][2] * rhs.z,
			mels[1][0] * rhs.x + mels[1][1] * rhs.y + mels[1][2] * rhs.z,
			mels[2][0] * rhs.x + mels[2][1] * rhs.y + mels[2][2] * rhs.z
		);
	}

	Matrix3 Matrix3::operator*(float rhs) const
	{
		float temp[9];

		for (int i = 0; i < 9; i++)
		{
			temp[i] = elements[i] * rhs;
		}

		return Matrix3(temp);
	}

	Matrix3 Matrix3::operator+(const Matrix3& rhs) const
	{
		float temp[9];

		for (int i = 0; i < 9; i++)
		{
			temp[i] = elements[i] + rhs.elements[i];
		}

		return Matrix3(temp);
	}

	Matrix3 Matrix3::operator-(const Matrix3& rhs) const
	{
		float temp[9];

		for (int i = 0; i < 9; i++)
		{
			temp[i] = elements[i] - rhs.elements[i];
		}

		return Matrix3(temp);
	}

	void Matrix3::SetScale(const Vector3& scale)
	{
		mels[0][0] = scale.x;
		mels[1][1] = scale.y;
		mels[2][2] = scale.z;
	}

	void Matrix3::SetScale(float scale)
	{
		mels[0][0] = scale;
		mels[1][1] = scale;
		mels[2][2] = scale;
	}

	Vector3 Matrix3::Scale() const
	{
		return Vector3(
			mels[0][0] * mels[0][0] + mels[1][0] * mels[1][0] + mels[2][0] * mels[2][0],
			mels[0][1] * mels[0][1] + mels[1][1] * mels[1][1] + mels[2][1] * mels[2][1],
			mels[0][2] * mels[0][2] + mels[1][2] * mels[1][2] + mels[2][2] * mels[2][2]
		);
	}

	Matrix3 Matrix3::Inverse() const
	{
		
		float d = 1.0f / (
			mels[0][0] * mels[1][1] * mels[2][2] +
			mels[1][0] * mels[2][1] * mels[0][2] +
			mels[2][0] * mels[0][1] * mels[1][2] -
			mels[2][0] * mels[1][1] * mels[0][2] -
			mels[1][0] * mels[0][1] * mels[2][2] -
			mels[0][0] * mels[2][1] * mels[1][2]);

		float temp[9] = {
			 (mels[1][1] * mels[2][2] - mels[2][1] * mels[1][2]) * d,
			-(mels[0][1] * mels[2][2] - mels[2][1] * mels[0][2]) * d,
			 (mels[0][1] * mels[1][2] - mels[1][1] * mels[0][2]) * d,
			-(mels[1][0] * mels[2][2] - mels[2][0] * mels[1][2]) * d,
			 (mels[0][0] * mels[2][2] - mels[2][0] * mels[0][2]) * d,
			-(mels[0][0] * mels[1][2] - mels[1][0] * mels[0][2]) * d,
			 (mels[1][0] * mels[2][1] - mels[2][0] * mels[1][1]) * d,
			-(mels[0][0] * mels[2][1] - mels[2][0] * mels[0][1]) * d,
			 (mels[0][0] * mels[1][1] - mels[1][0] * mels[0][1]) * d
		};

		return Matrix3(temp);
	}

	Matrix3 Matrix3::Transponse() const
	{
		float temp[9];

		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				temp[x * y * 3] = elements[y * x * 3];
			}
		}

		return Matrix3(temp);
	}

	String Matrix3::ToString() const
	{
		return String(mels[0][0]) + String(mels[0][1]) + String(mels[0][2]) + "\n" +
			String(mels[1][0]) + String(mels[1][1]) + String(mels[1][2]) + "\n" +
			String(mels[2][0]) + String(mels[2][1]) + String(mels[2][2]) + "\n";
 	}

}