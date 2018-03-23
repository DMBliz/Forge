#include "Sprite.h"
#include "FileSystem/FileSystem.h"
#include "Resources/Resources.h"
#include "Shader.h"
#include "Core/Engine.h"
#include "Math/Frustum.h"

namespace Forge
{

	Sprite::Sprite()
	{
		_mesh = new Mesh();
		_material = new Material();

		
		Shader* sh = engine->GetResources()->LoadNowResource<Shader>("Resources/Shaders/SpriteShader.glsl");

		_material->SetShader(sh);
		_material->AddTexture(nullptr, "spriteTexture");
		_material->Uniforms().AddUniform("projection", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("view", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("model", UniformDataType::MATRIX4);
		_material->Uniforms().AddUniform("spriteTexture", UniformDataType::SAMPLER2D);

		

        _mesh->GetVertecies().push_back(Vector3(0.5f, 0.5f, 0.0f));
        _mesh->GetVertecies().push_back(Vector3(0.5f, -0.5f, 0.0f));
        _mesh->GetVertecies().push_back(Vector3(-0.5f, -0.5f, 0.0f));
        _mesh->GetVertecies().push_back(Vector3(-0.5f, 0.5f, 0.0f));

        _mesh->GetUV().push_back(Vector2(1.0f, 1.0f));
        _mesh->GetUV().push_back(Vector2(1.0f, 0.0f));
        _mesh->GetUV().push_back(Vector2(0.0f, 0.0f));
        _mesh->GetUV().push_back(Vector2(0.0f, 1.0f));

		
        _mesh->GetIndicies().push_back(0);
        _mesh->GetIndicies().push_back(1);
        _mesh->GetIndicies().push_back(3);
        _mesh->GetIndicies().push_back(1);
        _mesh->GetIndicies().push_back(2);
        _mesh->GetIndicies().push_back(3);

		BufferLayout bl;
		bl.Add<Vector3>("pos", 0, BufferElementType::Position);
		bl.Add<Vector2>("textureCoords", 1, BufferElementType::UV);
		_mesh->SetBufferLayout(bl);
		_mesh->Initialize();
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
        Image img;
        img.Create(Vector2i(1, 1), color);
        Texture2D* texture = new Texture2D();
        texture->CreateOnGPU(img, TextureParametrs(), false);
        
		_material->SetTexture(texture, "spriteTexture");
	}

	void Sprite::SetPivotPosition(const Vector2& pivot)
	{
		_pivot = pivot;
	}

    void Sprite::Draw() const 
    {
        Renderer* renderer = engine->GetRenderer();
        _material->Uniforms().SetValueToUniform<Matrix4>("projection", renderer->GetFrustum().GetMatrix());
        _material->Uniforms().SetValueToUniform<Matrix4>("view", renderer->GetCamera().GetViewMatrix());
        _material->Uniforms().SetValueToUniform<Matrix4>("model", worldTransform->ToMatrix4());
        Drawable::Draw();
    }
}
