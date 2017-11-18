#include "Matrix4.h"
#include "Mathf.h"

namespace Forge 
{ 

	const Matrix4 Matrix4::Identity(1.0f);

	Matrix4::Matrix4()
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	Matrix4::Matrix4(float values[16])
	{
		memcpy(elements, values, 4 * 4 * sizeof(float));
	}

	Matrix4::Matrix4(float diagonal)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Matrix4::Matrix4(Matrix4& other)
	{
		memcpy(elements, other.elements, 4 * 4 * sizeof(float));
	}

	Matrix4& Matrix4::Multiply(const Matrix4& other)
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

	Vector4 Matrix4::Multiply(const Vector4& other) const
	{
		return Vector4(
			vectors[0].x * other.x + vectors[0].y * other.y + vectors[0].z * other.z + vectors[0].w * other.w,
			vectors[1].x * other.x + vectors[1].y * other.y + vectors[1].z * other.z + vectors[1].w * other.w,
			vectors[2].x * other.x + vectors[2].y * other.y + vectors[2].z * other.z + vectors[2].w * other.w,
			vectors[3].x * other.x + vectors[3].y * other.y + vectors[3].z * other.z + vectors[3].w * other.w
		);
	}

	Vector3 Matrix4::Multiply(const Vector3& other) const
	{
		return Vector3(
			vectors[0].x * other.x + vectors[0].y * other.y + vectors[0].z * other.z + vectors[0].w,
			vectors[1].x * other.x + vectors[1].y * other.y + vectors[1].z * other.z + vectors[1].w,
			vectors[2].x * other.x + vectors[2].y * other.y + vectors[2].z * other.z + vectors[2].w
		);
	}

	///Matrix invert
	/*Matrix4& Matrix4::Invert()
	{
		double temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0 / determinant;

		for (int i = 0; i < 4 * 4; i++)
			elements[i] = temp[i] * determinant;

		return *this;
	}*/

	Matrix4 operator*(Matrix4 lhs, const Matrix4& rhs)
	{
		return lhs.Multiply(rhs);
	}

	Vector4 operator*(const Matrix4& lhs, const Vector4& rhs)
	{
		return lhs.Multiply(rhs);
	}

	Vector3 operator*(const Matrix4& lhs, const Vector3& rhs)
	{
		return lhs.Multiply(rhs);
	}

	Matrix4& Matrix4::operator*=(const Matrix4& other)
	{
		return Multiply(other);
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

		res.elements[0 + 0 * 4] = 2.0f / (right - left);
		res.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		res.elements[2 + 2 * 4] = 2.0f / (near - far);

		res.elements[0 + 3 * 4] = (left + right) / (left - right);
		res.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		res.elements[2 + 3 * 4] = (far + near) / (far - near);

		return res;
	}

	Matrix4 Matrix4::Perspective(float fov, float aspectRetio, float near, float far)
	{
		Matrix4 res(1.0f);

		float q = 1.0f / (float)tan(fov * Forge::DEGTORAD);
		float a = q / aspectRetio;

		res.elements[0 + 0 * 4] = a;
		res.elements[1 + 1 * 4] = q;
		res.elements[2 + 2 * 4] = (near + far) / (near - far);
		res.elements[3 + 2 * 4] = -1.0f;
		res.elements[2 + 3 * 4] = (2.0f * near * far) / (near - far);

		return res;
	}

	Matrix4 Matrix4::Translation(const Vector3& translation)
	{
		Matrix4 res(1.0f);

		res.elements[0 + 3 * 4] = translation.x;
		res.elements[1 + 3 * 4] = translation.y;
		res.elements[2 + 3 * 4] = translation.z;

		return res;
	}

	Matrix4 Matrix4::Rotation(float angle, const Vector3& axis)
	{
		Matrix4 res(1.0f);

		float r = angle * Forge::DEGTORAD;
		float c = cos(r);
		float s = sin(r);
		float nc = 1.0f - c;

		/*res.elements[0 + 0 * 4] = axis.x * nc + c;
		res.elements[1 + 0 * 4] = axis.y * axis.x * nc + axis.z * s;
		res.elements[2 + 0 * 4] = axis.x * axis.z * nc - axis.y * s;

		res.elements[0 + 1 * 4] = axis.x * axis.y * nc - axis.z * s;
		res.elements[1 + 1 * 4] = axis.y * nc + c;
		res.elements[2 + 1 * 4] = axis.y * axis.z * nc + axis.x *s;

		res.elements[0 + 2 * 4] = axis.x * axis.z * nc + axis.y * s;
		res.elements[1 + 2 * 4] = axis.y * axis.z * nc - axis.x * s;
		res.elements[2 + 2 * 4] = axis.z * nc + c;*/

		res.elements[0 + 0 * 4] = axis.x * nc + c;
		res.elements[0 + 1 * 4] = axis.y * axis.x * nc + axis.z * s;
		res.elements[0 + 2 * 4] = axis.x * axis.z * nc - axis.y * s;

		res.elements[1 + 0 * 4] = axis.x * axis.y * nc - axis.z * s;
		res.elements[1 + 1 * 4] = axis.y * nc + c;
		res.elements[1 + 2 * 4] = axis.y * axis.z * nc + axis.x *s;

		res.elements[2 + 0 * 4] = axis.x * axis.z * nc + axis.y * s;
		res.elements[2 + 1 * 4] = axis.y * axis.z * nc - axis.x * s;
		res.elements[2 + 2 * 4] = axis.z * nc + c;

		return res;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		Matrix4 res(1.0f);

		res.elements[0 + 0 * 4] = scale.x;
		res.elements[1 + 1 * 4] = scale.y;
		res.elements[2 + 2 * 4] = scale.z;

		return res;
	}

	Matrix4::~Matrix4()
	{
	}
}