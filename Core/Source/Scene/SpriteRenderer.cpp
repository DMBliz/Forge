#include "SpriteRenderer.h"
#include "Scene/Entity.h"
#include "Core/Engine.h"
#include "TransformComponent.h"
#include "Graphics/Texture2D.h"

namespace Forge
{
	SpriteRenderer::SpriteRenderer()
	{
		sprite = new Sprite();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete sprite;
	}

	void SpriteRenderer::SetTexture(Texture2D* texture)
	{
		sprite->SetTexture(texture);
	}

	Texture2D* SpriteRenderer::GetTexture() const
	{
		return sprite->GetTexture();
	}

    void SpriteRenderer::Update()
    {
        sprite->Draw();
    }

    void SpriteRenderer::OnEnable()
	{
		sprite->SetActive(true);
		TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
		if (trn != nullptr)
		{
			sprite->SetWorldPosition(*trn->GetWorldTransform());
		}
	}

	void SpriteRenderer::OnDisable()
	{
		sprite->SetActive(false);
	}
}
