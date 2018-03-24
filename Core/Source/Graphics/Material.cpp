#include "Material.h"
#include "Defines.h"

namespace Forge
{
    void Material::ResolveUniforms()
    {

        for (auto it = uniforms.begin(); it != uniforms.end(); )
        {
            if (it->second->locationResolved)
            {
                ++it;
                continue;
            }

            int location = shader->ResolveUniformLocation(it->second->name);
            if (location >= 0)
            {
                LOG("Shader: " + shader->GetResourceName() + " does not contain such: " + it->second->name + " uniform");
                it->second->location = location;
                it->second->locationResolved = true;

                ++it;
            }
            else
            {
                uniforms.erase(it->first);
            }
        }
    }

    void Material::SetTextureSlots()
    {
        uint slot = 0;
        for (auto& uniform : uniforms)
        {
            if (uniform.second->type == UniformDataType::SAMPLER2D)
            {
                uniform.second->SetValueTextureSlot(slot);
                slot++;
            }
        }
    }

    Material::Material()
	{
	}

	Material::~Material()
	{
	}

	void Material::SetShader(Shader* newShader)
	{
		shader = newShader;
        for (auto& uniform : uniforms)
        {
		    uniform.second->location = shader->ResolveUniformLocation(uniform.second->name);
            uniform.second->locationResolved = true;
        }
	}

    UniformDescription* Material::GetUniform(const String& uniformName)
    {
        dirty = true;
        if(shader != nullptr)
        {
            if(uniforms[uniformName.CString()] != nullptr)
            {
                return uniforms[uniformName.CString()];
            }

            int location = shader->ResolveUniformLocation(uniformName);
            if (location >= 0)
            {
                UniformDescription* desc = new UniformDescription();
                desc->name = uniformName;
                desc->location = location;
                desc->locationResolved = true;
                uniforms.insert_or_assign(uniformName.CString(), desc);
                return desc;
            }else
            {
                LOG("Uniform with name: " + uniformName + " dosen't exist");
                UniformDescription* desc = new UniformDescription();
                desc->name = uniformName;
                uniforms.insert_or_assign(uniformName.CString(), desc);
                return desc;
            }
        }

        UniformDescription* desc = new UniformDescription();
        desc->name = uniformName;
        uniforms.insert_or_assign(uniformName.CString(), desc);
        return desc;
    }

    void Material::Use()
	{
        if(shader == nullptr)
        {
            LOG("Cannot use material without shader");
            return;
        }
		if(dirty)
		{
            ResolveUniforms();
            SetTextureSlots();
			dirty = false;
		}
		shader->Use();
        for (auto& uniform : uniforms)
        {
            shader->SetValueToUniform(*uniform.second);
        }
	}
}
