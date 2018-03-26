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

    const Matrix3x4* Drawable::GetWorldPosition() const
    {
        return _worldTransform;
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
		_worldTransform = &newPosition;
	}

    void Drawable::Draw() const
    {
        if (active)
        {
            DrawCommand command;
            command._mesh = _mesh;
            command._material = _material;
            command.transparent = _transparent;
            command.worldTransform = _worldTransform->ToMatrix4();
            engine->GetRenderer()->PushCommand(command);
        }
    }

    void Drawable::SetActive(bool state)
	{
		if (state == active)
			return;

		if(state)
		{
			active = state;
		}
		else
		{
			active = state;
		}
	}
}
