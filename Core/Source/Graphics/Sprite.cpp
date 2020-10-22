#include "Sprite.h"
#include "Platform/Api/FileSystem.h"
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

		
		Shader* sh = engine->getResources()->LoadNowResource<Shader>("Resources/Shaders/SpriteShader.glsl");

		_material->SetShader(sh);
		

        _mesh->GetVertecies().emplace_back(-0.5f, 0.5f, 0.0f);
        _mesh->GetVertecies().emplace_back(-0.5f, -0.5f, 0.0f);
        _mesh->GetVertecies().emplace_back(0.5f, -0.5f, 0.0f);
        _mesh->GetVertecies().emplace_back(0.5f, 0.5f, 0.0f);

        _mesh->GetUV().emplace_back(1.0f, 1.0f);
        _mesh->GetUV().emplace_back(1.0f, 0.0f);
        _mesh->GetUV().emplace_back(0.0f, 0.0f);
        _mesh->GetUV().emplace_back(0.0f, 1.0f);

		
        _mesh->GetIndicies().push_back(0);
        _mesh->GetIndicies().push_back(1);
        _mesh->GetIndicies().push_back(2);
        _mesh->GetIndicies().push_back(0);
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
        _texture = texture;
        _material->GetUniform("spriteTexture")->SetTexture(*texture);
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
        
        _material->GetUniform("spriteTexture")->SetTexture(*texture);
	}

	void Sprite::SetPivotPosition(const Vector2& pivot)
	{
		_pivot = pivot;
	}

    void Sprite::FlipX()
    {
        if (_texture == nullptr)
            return;

        Image* img = engine->getResources()->GetResource<Image>(_texture->GetResourceName());
        img->FlipX();
        _texture->SetTexture(*img);
    }

    void Sprite::FlipY()
    {
        if (_texture == nullptr)
            return;

        Image* img = engine->getResources()->GetResource<Image>(_texture->GetResourceName());
        img->FlipY();
        _texture->SetTexture(*img);
    }

    void Sprite::Draw() const 
    {
        Renderer* renderer = engine->getRenderer();
        _material->GetUniform("projection")->SetValue<Matrix4>(renderer->GetFrustum().GetMatrix());
        _material->GetUniform("view")->SetValue<Matrix4>(renderer->GetCamera().GetViewMatrix());
        _material->GetUniform("model")->SetValue<Matrix4>(_worldTransform->ToMatrix4());
        Drawable::Draw();
    }
}
