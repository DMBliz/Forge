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
		int ResolveUniformLocation(const String& uniformName) const;
		void SetSytemValueToUniform(UniformDescription& description) const;
		void SetValueToUniform(const UniformDescription& description) const;

		void Load(const String& filename) override;
		void UnLoad() override;
	};

}
