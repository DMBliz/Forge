#include "Quaternion.h"
#include "Mathf.h"

namespace Forge
{
	
	const Quaternion Quaternion::Identity;

	Quaternion::Quaternion()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{}

	Quaternion::Quaternion(float w, float x, float y, float z)
		: w(w), x(x), y(y), z(z)
	{}

	Quaternion::Quaternion(const Quaternion& quat)
		: w(quat.w), x(quat.x), y(quat.y), z(quat.z)
	{}

	Quaternion::Quaternion(float angle, const Vector3& axis)
	{
		FromAngleAxis(angle, axis);
	}

	Quaternion::Quaternion(float x, float y, float z)
	{
		FromEulerAngles(x, y, z);
	}

	Quaternion::Quaternion(const Vector3& start, const Vector3& end)
	{
		FromRotationTo(start, end);
	}

	Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		FromAxes(xAxis, yAxis, zAxis);
	}

	Quaternion::Quaternion(const Matrix3& matrix)
	{
		FromRotationMatrix(matrix);
	}

	bool Quaternion::operator==(const Quaternion& rhs) const
	{
		return w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool Quaternion::operator!=(const Quaternion& rhs) const
	{
		return w != rhs.w && x != rhs.x && y != rhs.y && z != rhs.z;
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-w, -x, -y, -z);
	}

	Quaternion& Quaternion::operator=(const Quaternion& rhs)
	{
		w = rhs.w;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	Quaternion& Quaternion::operator+=(const Quaternion& rhs)
	{
		w += rhs.w;
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& rhs)
	{
		w -= rhs.w;
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& rhs)
	{
		float nW = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
		float nX = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
		float nY = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
		float nZ = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;

		w = nW;
		x = nX;
		y = nY;
		z = nZ;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float rhs)
	{
		w *= rhs;
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& rhs) const
	{
		return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Quaternion Quaternion::operator-(const Quaternion& rhs) const
	{
		return Quaternion(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		return Quaternion(
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
			w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
			w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x
		);
	}

	Vector3 Quaternion::operator*(const Vector3& rhs) const
	{
		Vector3 temp(x, y, z);
		Vector3 c1(temp.Cross(rhs));
		Vector3 c2(temp.Cross(c1));

		return rhs + 2.0f * (c1 * w + c2);
	}

	Quaternion Quaternion::operator*(float rhs) const
	{
		return Quaternion(w * rhs, x * rhs, y * rhs, z  * rhs);
	}

	Quaternion operator*(float lhs, const Quaternion& rhs)
	{
		return Quaternion(rhs.w * lhs, rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
	}

	void Quaternion::FromAngleAxis(float angle, const Vector3& axis)
	{
		Vector3 norm = axis.Normalized();
		angle *= Forge::DEGTORAD_2;
		float s = sinf(angle);

		w = cosf(angle);
		x = norm.x * s;
		y = norm.y * s;
		z = norm.z * s;
	}

	void Quaternion::FromEulerAngles(float _x, float _y, float _z)
	{
		_x *= Forge::DEGTORAD_2;
		_y *= Forge::DEGTORAD_2;
		_z *= Forge::DEGTORAD_2;

		float sX = sinf(_x);
		float sY = sinf(_y);
		float sZ = sinf(_z);
		float cX = cosf(_x);
		float cY = cosf(_y);
		float cZ = cosf(_z);

		w = cY * cX * cZ + sY * sX * sZ;
		x = cY * sX * cZ + sY * cX * sZ;
		y = sY * cX * cZ - cY * sX * sZ;
		z = cY * cX * sZ - sY * sX * cZ;
	}

	void Quaternion::FromEulerAngles(const Vector3& vector)
	{
		float _x = vector.x * Forge::DEGTORAD_2;
		float _y = vector.y * Forge::DEGTORAD_2;
		float _z = vector.z * Forge::DEGTORAD_2;

		float sX = sinf(_x);
		float sY = sinf(_y);
		float sZ = sinf(_z);
		float cX = cosf(_x);
		float cY = cosf(_y);
		float cZ = cosf(_z);

		w = cY * cX * cZ + sY * sX * sZ;
		x = cY * sX * cZ + sY * cX * sZ;
		y = sY * cX * cZ - cY * sX * sZ;
		z = cY * cX * sZ - sY * sX * cZ;
	}

	void Quaternion::FromRotationTo(const Vector3& start, const Vector3& end)
	{
		Vector3 nStart = start.Normalized();
		Vector3 nEnd = end.Normalized();
		float d = nStart.Dot(nEnd);

		if (d > -1.0f + EPSILON)
		{
			Vector3 c = nStart.Cross(nEnd);
			float s = sqrt((1.0f + d) * 2.0f);
			float iS = 1.0f / s;

			x = c.x * iS;
			y = c.y * iS;
			z = c.z * iS;
			w = 0.5f * s;
		}
		else
		{
			Vector3 axis = Vector3::Right.Cross(nStart);
			if (axis.Length() < EPSILON)
				axis = Vector3::Up.Cross(nStart);

			FromAngleAxis(180.0f, axis);
		}
	}

	void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		float tmp[9] = {
			xAxis.x, yAxis.x, zAxis.x,
			xAxis.y, yAxis.y, zAxis.y,
			xAxis.z, yAxis.z, zAxis.z };
		FromRotationMatrix(Matrix3(tmp));
	}

	void Quaternion::FromRotationMatrix(const Matrix3& matrix)
	{
		float t = matrix.mels[0][0] + matrix.mels[1][1] + matrix.mels[2][2];

		if (t > 0.0f)
		{
			float s = 0.5f / sqrtf(1.0f + t);

			x = (matrix.mels[2][1] - matrix.mels[1][2]) * s;
			y = (matrix.mels[0][2] - matrix.mels[2][0]) * s;
			z = (matrix.mels[1][0] - matrix.mels[0][1]) * s;
			w = 0.25f / s;
		}
		else
		{
			if (matrix.mels[0][0] > matrix.mels[1][1] && matrix.mels[0][0] > matrix.mels[2][2])
			{
				float s = 0.5f / sqrtf(1.0f + matrix.mels[0][0] - matrix.mels[1][1] - matrix.mels[2][2]);

				x = 0.25f / s;
				y = (matrix.mels[0][1] + matrix.mels[1][0]) * s;
				z = (matrix.mels[2][0] + matrix.mels[0][2]) * s;
				w = (matrix.mels[2][1] - matrix.mels[1][2]) * s;
			}
			else if (matrix.mels[1][1] > matrix.mels[2][2])
			{
				float s = 0.5f / sqrtf(1.0f + matrix.mels[1][1] - matrix.mels[0][0] - matrix.mels[2][2]);

				x = (matrix.mels[0][1] + matrix.mels[1][0]) * s;
				y = 0.25f / s;
				z = (matrix.mels[1][2] + matrix.mels[2][1]) * s;
				w = (matrix.mels[0][2] - matrix.mels[2][0]) * s;
			}
			else
			{
				float s = 0.5f / sqrtf(1.0f + matrix.mels[2][2] - matrix.mels[0][0] - matrix.mels[1][1]);

				x = (matrix.mels[0][2] + matrix.mels[2][0]) * s;
				y = (matrix.mels[1][2] + matrix.mels[2][1]) * s;
				z = 0.25f / s;
				w = (matrix.mels[1][0] - matrix.mels[0][1]) * s;
			}
		}
	}

	void Quaternion::FromLookRotation(const Vector3& direction, const Vector3& up /*= Vector3::Up*/)
	{
		Quaternion ret;
		Vector3 forward = direction.Normalized();

		Vector3 v = forward.Cross(up);

		if (v.LengthSquared() >= EPSILON)
		{
			v.Normalize();
			Vector3 rUp = v.Cross(forward);
			Vector3 rRight = rUp.Cross(forward);

			ret.FromAxes(rRight, rUp, forward);
		}
		else
			ret.FromRotationTo(Vector3::Forward, forward);
	}

	void Quaternion::Nomalize()
	{
		float lenSquared = LengthSquared();

		if (lenSquared != 1.0f && lenSquared > 0.0f)
		{
			float iLen = 1.0f / sqrtf(lenSquared);

			w *= iLen;
			x *= iLen;
			y *= iLen;
			z *= iLen;
		}
	}

	Quaternion Quaternion::Normalized() const
	{
		float lenSquared = LengthSquared();

		if (lenSquared != 1.0f && lenSquared > 0.0f)
		{
			float iLen = 1.0f / sqrtf(lenSquared);

			return *this * iLen;
		}
		else
			return *this;
	}

	Quaternion Quaternion::Inverse() const
	{
		float lenSquared = LengthSquared();

		if (lenSquared == 1.0f)
			return Conjugate();
		else if (lenSquared >= EPSILON)
			return Conjugate() * (1.0f / lenSquared);
		else
			return Identity;
	}

	float Quaternion::LengthSquared() const
	{
		return w * w + x * x + y * y + z * z;
	}
	
	float Quaternion::Dot(const Quaternion& rhs) const
	{
		return w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(w, -x, -y, -z);
	}

	Vector3 Quaternion::EulerAngles() const
	{
		float check = 2.0f * (-y * z + w * x);

		if (check < -0.995f)
		{
			return Vector3(
				-90.0f,
				0.0f,
				-atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RADTODEG
			);
		}
		else if(check > 0.995f)
		{
			return Vector3(
				90.0f,
				0.0f,
				atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RADTODEG
			);
		}
		else
		{
			return Vector3(
				asinf(check) * RADTODEG,
				atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * RADTODEG,
				atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * RADTODEG
			);
		}
	}

	Vector3 Quaternion::Axis() const
	{
		return Vector3(x, y, z) / sqrt(1 - w * w);
	}

	float Quaternion::Angle() const
	{
		return 2 * Acos(w);
	}

	Matrix3 Quaternion::RotationMatrix() const
	{
		float tmp[9] = {
			1.0f - 2.0f * y * y - 2.0f * z * z,
			2.0f * x * y - 2.0f * w * z,
			2.0f * x * z + 2.0f * w * y,
			2.0f * x * y + 2.0f * w * z,
			1.0f - 2.0f * x * x - 2.0f * z * z,
			2.0f * y * z - 2.0f * w * x,
			2.0f * x * z - 2.0f * w * y,
			2.0f * y * z + 2.0f * w * x,
			1.0f - 2.0f * x * x - 2.0f * y * y
		};

		return Matrix3(tmp);
	}

	Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t)
	{
		float d = a.Dot(b);
		float flip = d >= 0.0f ? 1.0f : -1.0f;

		return flip * (1.0f - t) * a + t * b;
	}

	Quaternion Quaternion::Slerp(const Quaternion& rhs, float t) const
	{
		float d = Dot(rhs);
		float sign = 1.0f;

		if (d < 0.0f)
		{
			d = -d;
			sign = -1.0f;
		}

		float angle = acosf(d);
		float sinAngle = sinf(angle);
		float t1, t2;

		if (sinAngle > 0.001f)
		{
			float iSinAngle = 1.0f / sinAngle;
			t1 = sinf((1.0f - t) * angle) * iSinAngle;
			t2 = sinf(t * angle) * iSinAngle;
		}
		else
		{
			t1 = 1.0f - t;
			t2 = t;
		}

		return *this * t1 + (rhs * sign) * t2;
	}

	Quaternion Quaternion::Nlerp(const Quaternion& rhs, float t, bool shortPath/* = false*/) const
	{
		Quaternion res;
		float d = Dot(rhs);

		if (d < 0.0f && shortPath)
			res = *this + ((-rhs - *this) * t);
		else
			res = *this + ((rhs - *this) * t);

		res.Nomalize();
		return res;
	}

    Vector3 Quaternion::Rotate(const Quaternion& quaternion, const Vector3& vector)
    {
        float tmpX, tmpY, tmpZ, tmpW;
        tmpX = (((quaternion.w * vector.x) + (quaternion.y * vector.z)) - (quaternion.z * vector.y));
        tmpY = (((quaternion.w * vector.y) + (quaternion.z * vector.x)) - (quaternion.x * vector.z));
        tmpZ = (((quaternion.w * vector.z) + (quaternion.x * vector.y)) - (quaternion.y * vector.x));
        tmpW = (((quaternion.x * vector.x) + (quaternion.y * vector.y)) + (quaternion.z * vector.z));
        return Vector3(
            ((((tmpW * quaternion.x) + (tmpX * quaternion.w)) - (tmpY * quaternion.z)) + (tmpZ * quaternion.y)),
            ((((tmpW * quaternion.y) + (tmpY * quaternion.w)) - (tmpZ * quaternion.x)) + (tmpX * quaternion.z)),
            ((((tmpW * quaternion.z) + (tmpZ * quaternion.w)) - (tmpX * quaternion.y)) + (tmpY * quaternion.x))
        );
    }

    String Quaternion::ToString() const
	{
		return "(" + String(w) + ", " + String(x) + ", " + String(y) + ", " + String(z) + ")\n";
	}

	Quaternion Quaternion::FromEuler(const Vector3& rotation)
	{
		float _x = rotation.x * Forge::DEGTORAD_2;
		float _y = rotation.y * Forge::DEGTORAD_2;
		float _z = rotation.z * Forge::DEGTORAD_2;

		float sX = sinf(_x);
		float sY = sinf(_y);
		float sZ = sinf(_z);
		float cX = cosf(_x);
		float cY = cosf(_y);
		float cZ = cosf(_z);

		float w = cY * cX * cZ + sY * sX * sZ;
		float x = cY * sX * cZ + sY * cX * sZ;
		float y = sY * cX * cZ - cY * sX * sZ;
		float z = cY * cX * sZ - sY * sX * cZ;

		return Quaternion(w, x, y, z);
	}

	Quaternion Quaternion::FromEuler(float x, float y, float z)
	{
		float _x = x * Forge::DEGTORAD_2;
		float _y = y * Forge::DEGTORAD_2;
		float _z = z * Forge::DEGTORAD_2;

		float sX = sinf(_x);
		float sY = sinf(_y);
		float sZ = sinf(_z);
		float cX = cosf(_x);
		float cY = cosf(_y);
		float cZ = cosf(_z);

		float rw = cY * cX * cZ + sY * sX * sZ;
		float rx = cY * sX * cZ + sY * cX * sZ;
		float ry = sY * cX * cZ - cY * sX * sZ;
		float rz = cY * cX * sZ - sY * sX * cZ;

		return Quaternion(rw, rx, ry, rz);
	}

	Vector3 Quaternion::ToEuler(const Quaternion& rotation)
	{
		float w = rotation.w;
		float x = rotation.x;
		float y = rotation.y;
		float z = rotation.z;
		float check = 2.0f * (-y * z + w * x);

		if (check < -0.995f)
		{
			return Vector3(
				-90.0f,
				0.0f,
				-atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RADTODEG
			);
		}
		else if (check > 0.995f)
		{
			return Vector3(
				90.0f,
				0.0f,
				atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RADTODEG
			);
		}
		else
		{
			return Vector3(
				asinf(check) * RADTODEG,
				atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * RADTODEG,
				atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * RADTODEG
			);
		}
	}


}

