#pragma once
#include "Resources/Resource.h"
#include "Graphics/ShaderResource.h"

namespace Forge
{

	class Shader : public Resource
	{
	private:
		ShaderResource* shaderResource;
	public:
		Shader();
		explicit Shader(String filename);
		~Shader();

		void Use();
		void Compile();
		void ResolveUniformLocations(ShaderUniforms& uniforms) const;
		void SetSytemValueToUniform(UniformDescription& description) const;
		void SetValueToUniform(const UniformDescription& description) const;
		void SetValuesToUniforms(const ShaderUniforms& uniforms) const;

		void Load(String filename) override;
		void UnLoad() override;
	};

}
