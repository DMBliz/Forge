#include "ShaderUniform.h"
#include "Defines.h"
#include "Texture2DResource.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Matrix4.h"
#include "Math/Matrix3.h"
#include "Texture2D.h"

namespace Forge
{

	void UniformDescription::DeleteData()
	{
		switch (type)
		{
			case UniformDataType::FLOAT:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
			case UniformDataType::VECTOR2:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
			case UniformDataType::VECTOR3:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
			case UniformDataType::VECTOR4:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
			case UniformDataType::INTEGER:
			{
				delete[] reinterpret_cast<int*>(data);
				break;
			}
			case UniformDataType::VECTOR2I:
			{
				delete[] reinterpret_cast<int*>(data);
				break;
			}
			case UniformDataType::UNSIGNED_INTEGER:
			{
				delete[] reinterpret_cast<uint*>(data);
				break;
			}
			case UniformDataType::COLOR:
			{
				delete[] reinterpret_cast<Color*>(data);
				break;
			}
			case UniformDataType::MATRIX3:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
			case UniformDataType::MATRIX4:
			{
				delete[] reinterpret_cast<float*>(data);
				break;
			}
		}
	}

    void UniformDescription::SetName(const String& name)
    {
        this->name = name;
    }

    template <typename T>
    void UniformDescription::SetValue(uint count, T* value)
	{
        LOG("Trying set wrong data type");
	}

    template <typename T>
    void UniformDescription::SetValue(T value)
    {
        LOG("Trying set wrong data type");
    }

    void UniformDescription::SetTexture(const Texture2D& texture)
    {
        type = UniformDataType::SAMPLER2D;
        _count = -1;
        data = new uint(texture.GetID());
    }

    void UniformDescription::SetTexture(uint textureID)
    {
        type = UniformDataType::SAMPLER2D;
        _count = -1;
        data = new uint(textureID);
    }

    void UniformDescription::SetValueTextureSlot(uint slot)
	{
        _count = slot;
	}

    template <>
    void UniformDescription::SetValue<int>(int value)
    {
        type = UniformDataType::INTEGER;
        _count = 1;
        data = new int(value);
    }

    template <>
    void UniformDescription::SetValue<float>(float value)
    {
        type = UniformDataType::FLOAT;
        _count = 1;
        data = new float(value);
    }

    template <>
    void UniformDescription::SetValue<uint>(uint value)
    {
        type = UniformDataType::UNSIGNED_INTEGER;
        _count = 1;
        data = new uint(value);
    }

    template <>
    void UniformDescription::SetValue<Vector2>(Vector2 value)
    {
        type = UniformDataType::VECTOR2;
        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[2];
        memcpy(data, &value, 2 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Vector2i>(Vector2i value)
    {
        
        type = UniformDataType::VECTOR2I;
        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<int*>(data);

        data = new int[2];
        memcpy(data, &value, 2 * sizeof(int));
    }

    template <>
    void UniformDescription::SetValue<Vector3>(Vector3 value)
    {
        type = UniformDataType::VECTOR3;
        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[3];
        memcpy(data, &value, 3 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Vector4>(Vector4 value)
    {
        type = UniformDataType::VECTOR4;
        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[4];
        memcpy(data, &value, 4 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Color>(Color value)
    {
        type = UniformDataType::COLOR;
        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<Color*>(data);

        data = new Color;
        memcpy(data, &value, sizeof(Color));
    }

    template <>
    void UniformDescription::SetValue<Matrix3>(Matrix3 value)
    {
        type = UniformDataType::MATRIX3;

        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[9];
        memcpy(data, &value, 9 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Matrix4>(Matrix4 value)
    {
        type = UniformDataType::MATRIX4;

        _count = 1;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[16];
        memcpy(data, &value, 16 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<int>(uint count, int* value)
    {
        type = UniformDataType::INTEGER;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<int*>(data);

        data = new int[_count];
        memcpy(data, value, _count * sizeof(int));
    }

    template <>
    void UniformDescription::SetValue<float>(uint count, float* value)
    {
        type = UniformDataType::FLOAT;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count];
        memcpy(data, value, _count * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<uint>(uint count, uint* value)
    {
        type = UniformDataType::UNSIGNED_INTEGER;


        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<uint*>(data);

        data = new uint[_count * sizeof(uint)];
        memcpy(data, value, _count * sizeof(uint));
    }

    template <>
    void UniformDescription::SetValue<Vector2>(uint count, Vector2* value)
    {
        type = UniformDataType::VECTOR2;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count * 2];
        memcpy(data, value, _count * 2 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Vector2i>(uint count, Vector2i* value)
    {
        type = UniformDataType::VECTOR2I;


        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<int*>(data);

        data = new int[_count * 2];
        memcpy(data, value, _count * 2 * sizeof(int));
    }

    template <>
    void UniformDescription::SetValue<Vector3>(uint count, Vector3* value)
    {
        type = UniformDataType::VECTOR3;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count * 3];
        memcpy(data, value, _count * 3 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Vector4>(uint count, Vector4* value)
    {
        type = UniformDataType::VECTOR4;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count * 4];
        memcpy(data, value, _count * 4 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Color>(uint count, Color* value)
    {
        type = UniformDataType::COLOR;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<Color*>(data);

        data = new Color[_count];
        memcpy(data, value, _count * sizeof(Color));
    }

    template <>
    void UniformDescription::SetValue<Matrix3>(uint count, Matrix3* value)
    {
        type = UniformDataType::MATRIX3;


        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count * 9];
        memcpy(data, value, _count * 9 * sizeof(float));
    }

    template <>
    void UniformDescription::SetValue<Matrix4>(uint count, Matrix4* value)
    {
        type = UniformDataType::MATRIX4;

        _count = count;

        if (data != nullptr)
            delete[] reinterpret_cast<float*>(data);

        data = new float[_count * 16];
        memcpy(data, value, _count * 16 * sizeof(float));
    }

}
