#pragma once
#include "Graphics/ShaderResource.h"

namespace Forge
{

	class GLShaderResource : public ShaderResource
	{
	private:
		String GetBlock(const String& blockName);
	public:
		GLShaderResource();
		~GLShaderResource();

		void LoadShader(const String& filename) override;

		void Compile() override;
		void Use() override;

		void SetValuesToUniforms(const ShaderUniforms& unifroms) override;
		void SetValueToUniform(const UniformDescription& desc) override;
		void SetSystemValueToUniform(UniformDescription& desc) override;
		void ResolveUniformLocations(ShaderUniforms& unifroms) override;

	}; 

}
