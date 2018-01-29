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

	void SpriteRenderer::OnEnable()
	{
		sprite->SetActive(true);
		
		sprite->SetPosition(*GetOwner()->GetComponent<TransformComponent>()->GetWorldTransform());
	}

	void SpriteRenderer::OnDisable()
	{
		sprite->SetActive(false);
	}
}
