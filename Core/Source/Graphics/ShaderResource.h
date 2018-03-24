#pragma once
#include "Containers/String.h"
#include "ShaderUniform.h"
#include "Resources/Resource.h"

namespace Forge
{
	class File;
	class ShaderResource
	{
	protected:
		String shaderSource;
		String vertexShader;
		String fragmentShader;

		unsigned int programID;

	public:

		virtual void LoadShader(const String& filename) = 0;

		virtual void Compile() = 0;
		virtual void Use() = 0;

        virtual int ResolveUniformLocation(const String& uniformName) = 0;
		virtual void SetValueToUniform(const UniformDescription& desc) = 0;
		virtual void SetSystemValueToUniform(UniformDescription& desc) = 0;

		static ShaderResource* Create();
	};
}
