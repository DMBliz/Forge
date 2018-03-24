#pragma once
#include <vector>
#include "ShaderResource.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "Shader.h"
#include <map>

namespace Forge
{
	struct TextureDesc
	{
		Texture* texture;
		String uniformName;
		bool dirty = true;


		TextureDesc(Texture* texture, const String& uniformName)
			: texture(texture), uniformName(uniformName)
		{}
	};

	class Material
	{
	private:
		Shader* shader;
        std::map<std::string, UniformDescription*> uniforms;
		bool dirty = false;

        void ResolveUniforms();
        void SetTextureSlots();
	public:
		Material();
		~Material();

		void SetShader(Shader* newShader);

        UniformDescription* GetUniform(const String& uniformName);
		
		void Use();

		Shader* GetShader() const { return shader;  }
	};

}
