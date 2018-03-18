#include "Drawable.h"
#include "Core/Engine.h"

namespace Forge
{

	Drawable::Drawable()
		: _material(new Material()), _mesh(new Mesh())
	{
	}

	Drawable::~Drawable()
	{}

	void Drawable::OnActivate()
	{
		Renderer* rend = engine->GetRenderer();
		if (!rend->ContainsDrawable(this))
			rend->AddDrawable(this);
	}

	void Drawable::OnDeactivate()
	{
		Renderer* rend = engine->GetRenderer();
		if (rend->ContainsDrawable(this))
			rend->RemoveDrawable(this);
	}

    const Matrix3x4* Drawable::GetWorldPosition() const
    {
        return worldTransform;
    }

	Material& Drawable::GetMaterial() const
	{
		return *_material;
	}

	Mesh& Drawable::GetMesh() const
	{
		return *_mesh;
	}

	void Drawable::SetWorldPosition(const Matrix3x4& newPosition)
	{
		worldTransform = &newPosition;
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
