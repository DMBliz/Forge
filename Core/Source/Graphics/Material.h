#pragma once
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "BufferLayout.h"

namespace Forge
{
	struct TextureDesc
	{
		Texture* texture;
		String uniformName;
		bool dirty;


		TextureDesc(Texture* texture, const String& uniformName)
			: texture(texture), uniformName(uniformName)
		{}
	};

	class Material
	{
	private:
		std::vector<TextureDesc> _textures;
		Shader* shader = Shader::Create();
		ShaderUniforms uniforms;
		BufferLayout layout;
	public:
		Material();
		~Material();

		void AddTexture(Texture* texture, const String& uniformName);
		void SetTexture(Texture* texture, const String& uniformName);

		void SetShader(Shader* newShader);
		
		void Use();

		Shader* GetShader() const { return shader; }
		ShaderUniforms& Uniforms() { return uniforms; }
		std::vector<TextureDesc>& Textures() { return _textures; }
	};

}
