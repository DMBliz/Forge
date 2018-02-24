#include "Sprite.h"
#include "FileSystem/FileSystem.h"
#include "Resources/Resources.h"
#include "Shader.h"
#include "Core/Engine.h"

namespace Forge
{

	Sprite::Sprite()
	{
		_batches.push_back(new DrawBatch);
		_material = new Material;
		_batches[0]->material = _material;
		_batches[0]->mesh = new Mesh;

		
		Shader* sh = engine->GetResources()->LoadNowResource<Shader>("Resources/Shaders/SpriteShader.glsl");

		_material->SetShader(sh);
		_material->AddTexture(nullptr, "spriteTexture");
		_material->Uniforms().AddUniform("projection", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("view", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("model", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("spriteTexture", UniformDataType::SAMPLER2D);

		float vb[] = {
			 0.5f,  0.5f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f,   1.0f, 0.0f,
			-0.5f, -0.5f,  0.0f,   0.0f, 0.0f,
			-0.5f,  0.5f,  0.0f,   0.0f, 1.0f
		};

		uint ind[] = {
			0, 1, 3,
			1, 2, 3
		};

		BufferLayout bl;
		bl.Add<float>("pos", 0, 3, false);
		bl.Add<float>("textureCoords", 1, 2, false);

		_batches[0]->mesh->SetVertexBuffer(vb, 20, BufferUsage::STATIC);
		_batches[0]->mesh->SetIndexBuffer(ind, 6);
		_batches[0]->mesh->SetBufferLayout(bl);
		_batches[0]->mesh->Initialize();
	}

	Sprite::~Sprite()
	{}

	void Sprite::SetTexture(Texture2D* texture)
	{
		_material->SetTexture(texture, "spriteTexture");
	}

	void Sprite::SetMaterial(Material* material)
	{
		_material = material;
	}

	void Sprite::SetColor(const Color& color)
	{
		_material->Uniforms().SetValueToUniform<Color>("Color", color);
	}

	void Sprite::SetPivotPosition(const Vector2& pivot)
	{
		_pivot = pivot;
	}

	void Sprite::SetPosition(const Matrix3x4& position)
	{
		_batches[0]->worldTransform = &position;
		_material->Uniforms().SetValueToUniform("model", position.ToMatrix4());
	}
}
