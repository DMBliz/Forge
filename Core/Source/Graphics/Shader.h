#pragma once
#include "Containers/String.h"
#include "ShaderUniform.h"
#include "VertexArray.h"

namespace Forge
{
	class File;
	class Shader
	{
	protected:
		String shaderSource;
		String vertexShader;
		String fragmentShader;

		unsigned int programID;

	public:
		Shader();

		virtual void Init(const File& source) = 0;
		virtual void Init(const String& source) = 0;

		virtual void Compile() = 0;
		virtual void Use() = 0;
		virtual void SetValuesToUniforms(const ShaderUniforms& unifroms) = 0;
		virtual void SetValueToUniform(const UniformDescription& desc) = 0;
		virtual void SetSystemValueToUniform(UniformDescription& desc) = 0;
		virtual void ResolveUniformLocations(ShaderUniforms& unifroms) = 0;

		static Shader* Create();
	};

}
