#include "Drawable.h"
#include "Platform/Engine.h"

namespace Forge
{

	Drawable::Drawable()
	{}


	Drawable::~Drawable()
	{}

	void Drawable::OnActivate()
	{
		Renderer* rend = engine->GetRenderer();
		for (int i = 0; i < _batches.size(); ++i)
		{
			if (!rend->ContainsDrawBatch(_batches[i]))
				engine->GetRenderer()->AddDrawBatch(_batches[i]);
		}
	}

	void Drawable::OnDeactivate()
	{
		Renderer* rend = engine->GetRenderer();
		for (int i = 0; i < _batches.size(); ++i)
		{
			if (rend->ContainsDrawBatch(_batches[i]))
				engine->GetRenderer()->RemoveDrawBatch(_batches[i]);
		}
	}

	void Drawable::SetActive(bool state)
	{
		if (state == active)
			return;

		if(state)
		{
			OnActivate();
			active = state;
		}
		else
		{
			OnDeactivate();
			active = state;
		}
	}
}
