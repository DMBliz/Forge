#pragma once
#include "Graphics/Shader.h"

namespace Forge
{

	class OGLShader : public Shader
	{
	private:
		String GetBlock(const String& blockName);
	public:
		OGLShader();


		void Init(const File& source) override;
		void Init(const String& source) override;
		void Compile() override;
		void Use() override;

		void SetValuesToUniforms(const ShaderUniforms& unifroms) override;
		void SetValueToUniform(const UniformDescription& desc) override;
		void SetSystemValueToUniform(UniformDescription& desc) override;
		void ResolveUniformLocations(ShaderUniforms& unifroms) override;
	}; 

}
