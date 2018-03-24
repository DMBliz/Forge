#include "Shader.h"

namespace Forge
{

	Shader::Shader()
	{}

	Shader::Shader(String filename)
	{
		Load(filename);
	}

	Shader::~Shader()
	{
		
	}

	void Shader::Use()
	{
		shaderResource->Use();
	}

	void Shader::Compile()
	{
		shaderResource->Compile();
	}

    int Shader::ResolveUniformLocation(const String& uniformName) const
    {
        return shaderResource->ResolveUniformLocation(uniformName);
    }

	void Shader::SetSytemValueToUniform(UniformDescription& description) const
	{
		shaderResource->SetSystemValueToUniform(description);
	}

	void Shader::SetValueToUniform(const UniformDescription& description) const
	{
		shaderResource->SetValueToUniform(description);
	}

	void Shader::Load(const String& filename)
	{
		resourceName = filename;
		shaderResource = ShaderResource::Create();
		shaderResource->LoadShader(filename);
	}

	void Shader::UnLoad()
	{
		delete shaderResource;
	}
}
