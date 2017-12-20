#include "Material.h"

namespace Forge
{

	Material::Material()
	{
	}

	Material::~Material()
	{
		delete shader;
	}

	void Material::AddTexture(Texture* texture, const String& uniformName)
	{
		_textures.push_back(TextureDesc(texture,uniformName));
	}

	void Material::SetTexture(Texture* texture, const String& uniformName)
	{
		for (int i = 0; i < _textures.size(); ++i)
		{
			if(_textures[i].uniformName == uniformName)
			{
				_textures[i].texture = texture;
				_textures[i].dirty = true;
			}
		}
	}

	void Material::SetShader(Shader* newShader)
	{
		shader = newShader;
		shader->ResolveUniformLocations(uniforms);
	}

	void Material::Use()
	{
		shader->Use();
		for (int i = 0; i < _textures.size(); ++i)
		{
			if (_textures[i].dirty)
			{
				uniforms.SetTextureToUniform(_textures[i].uniformName, _textures[i].texture->GetID(), i);
				_textures[i].dirty = false;
			}
		}
		shader->SetValuesToUniforms(uniforms);
	}
}
