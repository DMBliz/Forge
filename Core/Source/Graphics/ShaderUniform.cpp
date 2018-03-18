#include "ShaderUniform.h"
#include "Defines.h"
#include "Texture2DResource.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Matrix4.h"
#include "Math/Matrix3.h"
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


	ShaderUniforms::ShaderUniforms()
	{}

	ShaderUniforms::~ShaderUniforms()
	{
		for (unsigned int i = 0; i < uniforms.size(); i++)
		{
			delete uniforms[i];
		}
	}

	int ShaderUniforms::FindUniformID(const String& name)
	{
		for (unsigned int i = 0; i < uniforms.size(); i++)
		{
			if (uniforms[i]->name == name)
				return i;
		}

		return -1;
	}

	void ShaderUniforms::AddUniform(UniformDescription* uniform)
	{
		uniforms.push_back(uniform);
	}

	void ShaderUniforms::AddUniform(const String& uniformName, UniformDataType dataType)
	{
		UniformDescription* uniform = new UniformDescription;
		uniform->name = uniformName;
		uniform->type = dataType;
		uniform->data = nullptr;

		uniforms.push_back(uniform);
	}

	UniformDescription* ShaderUniforms::operator[](uint index) const
	{
		return uniforms[index];
	}

	void ShaderUniforms::SetTextureToUniform(const String& uniformName, uint textureID, uint slot)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uint data[] = { slot, textureID };

		uniforms[id]->count = 1;
		uniforms[id]->data = new uint[2];
		memcpy(uniforms[id]->data, data, 2 * sizeof(uint));
	}

	template <typename T>
	void ShaderUniforms::SetValueToUniform(const String& uniformName, uint count, T* data)
	{
		LOG("Trying set wrong data type");
	}

	template <typename T>
	void ShaderUniforms::SetValueToUniform(const String& uniformName, T data)
	{
		LOG("Trying set wrong data type");
	}

	template <>
	void ShaderUniforms::SetValueToUniform<int>(const String& uniformName, int data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = 1;
		uniforms[id]->data = new int(data);
	}

	template <>
	void ShaderUniforms::SetValueToUniform<float>(const String& uniformName, float data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = 1;
		uniforms[id]->data = new float(data);
	}

	template <>
	void ShaderUniforms::SetValueToUniform<uint>(const String& uniformName, uint data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = 1;
		uniforms[id]->data = new uint(data);
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Color>(const String& uniformName, Color data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = 1;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<Color*>(uniforms[id]->data);

		uniforms[id]->data = new Color;
		memcpy(uniforms[id]->data, &data, sizeof(Color));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Matrix4>(const String& uniformName, Matrix4 data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = 1;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[16];
		memcpy(uniforms[id]->data, &data, 16 * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<int>(const String& uniformName, uint count, int* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<int*>(uniforms[id]->data);

		uniforms[id]->data = new int[count];
		memcpy(uniforms[id]->data, data, count * sizeof(int));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<float>(const String& uniformName, uint count, float* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count];
		memcpy(uniforms[id]->data, data, count * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<unsigned>(const String& uniformName, uint count, uint* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<uint*>(uniforms[id]->data);

		uniforms[id]->data = new uint[count * sizeof(uint)];
		memcpy(uniforms[id]->data, data, count * sizeof(uint));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Vector2>(const String& uniformName, uint count, Vector2* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count * 2];
		memcpy(uniforms[id]->data, data, count * 2 * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Vector2i>(const String& uniformName, uint count, Vector2i* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<int*>(uniforms[id]->data);

		uniforms[id]->data = new int[count * 2];
		memcpy(uniforms[id]->data, data, count * 2 * sizeof(int));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Vector3>(const String& uniformName, uint count, Vector3* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count * 3];
		memcpy(uniforms[id]->data, data, count * 3 * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Vector4>(const String& uniformName, uint count, Vector4* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count * 4];
		memcpy(uniforms[id]->data, data, count * 4 * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Color>(const String& uniformName, uint count, Color* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<Color*>(uniforms[id]->data);

		uniforms[id]->data = new Color[count];
		memcpy(uniforms[id]->data, data, count * sizeof(Color));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Matrix3>(const String& uniformName, uint count, Matrix3* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count * 9];
		memcpy(uniforms[id]->data, data, count * 9 * sizeof(float));
	}

	template <>
	void ShaderUniforms::SetValueToUniform<Matrix4>(const String& uniformName, uint count, Matrix4* data)
	{
		int id = FindUniformID(uniformName);
		if (id < 0)
		{
			LOG("Trying set unexisting uniform");
			return;
		}

		uniforms[id]->count = count;

		if (uniforms[id]->data != nullptr)
			delete[] reinterpret_cast<float*>(uniforms[id]->data);

		uniforms[id]->data = new float[count * 16];
		memcpy(uniforms[id]->data, data, count * 16 * sizeof(float));
	}
}
