#pragma once
#include <vector>
#include "ShaderResource.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "Shader.h"

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
		std::vector<TextureDesc> _textures;
		Shader* shader;
		ShaderUniforms uniforms;
		BufferLayout layout;
		bool dirty = false;
	public:
		Material();
		~Material();

		void AddTexture(Texture* texture, const String& uniformName);
		void SetTexture(Texture* texture, const String& uniformName);
		Texture* GetTexture(const String& uniformName) const;

		void SetShader(Shader* newShader);
		
		void Use();

		Shader* GetShader() const { return shader;  }
		ShaderUniforms& Uniforms() { dirty = true; return uniforms; }
		std::vector<TextureDesc>& Textures() { return _textures; }
	};

}
