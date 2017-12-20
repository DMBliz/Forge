#include "SpriteRenderer.h"
#include "Platform/Engine.h"
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
	}

	void SpriteRenderer::OnDisable()
	{
		sprite->SetActive(false);
	}
}
