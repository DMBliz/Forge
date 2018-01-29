#pragma once
#include "Types.h"
#include "Containers/String.h"
#include "Math/Mathf.h"

namespace Forge
{

	enum class UniformDataType
	{
		FLOAT,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		COLOR,
		INTEGER,
		VECTOR2I,
		UNSIGNED_INTEGER,
		MATRIX3,
		MATRIX4,
		SAMPLER2D
	};

	struct UniformDescription
	{
		String name;
		uint location;
		UniformDataType type;
		uint count;
		void* data = nullptr;
		bool locationResolved = false;

		~UniformDescription()
		{
			DeleteData();
		}

	private:
		using varType = void;

		void DeleteData();
	};

	class ShaderUniforms
	{
	private:
		std::vector<UniformDescription*> uniforms;
		int FindUniformID(const String& name);
	public:
		ShaderUniforms();
		~ShaderUniforms();
		
		int GetSize() const { return uniforms.size(); }
		UniformDescription* GetByID(int id) const { return uniforms[id]; }

		void AddUniform(UniformDescription* uniform);
		void AddUniform(const String& uniformName, UniformDataType dataType);

		UniformDescription* operator[](uint index) const;

		template<typename  T>
		void SetValueToUniform(const String& uniformName, uint count, T* data);

		template<typename  T>
		void SetValueToUniform(const String& uniformName, T data);

		void SetTextureToUniform(const String& uniformName, uint textureID, uint slot);
	};

}
