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
		UnLoad();
	}

	void Shader::Use()
	{
		shaderResource->Use();
	}

	void Shader::ResolveUniformLocations(ShaderUniforms& uniforms) const
	{
		shaderResource->ResolveUniformLocations(uniforms);
	}

	void Shader::SetSytemValueToUniform(UniformDescription& description) const
	{
		shaderResource->SetSystemValueToUniform(description);
	}

	void Shader::SetValueToUniform(const UniformDescription& description) const
	{
		shaderResource->SetValueToUniform(description);
	}

	void Shader::SetValuesToUniforms(const ShaderUniforms& uniforms) const
	{
		shaderResource->SetValuesToUniforms(uniforms);
	}

	void Shader::Load(String filename)
	{
		shaderResource = ShaderResource::Create();
		shaderResource->LoadShader(filename);
	}

	void Shader::UnLoad()
	{
		delete shaderResource;
	}
}
