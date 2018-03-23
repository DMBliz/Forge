#include "DirectionalLight.h"
#include "Core/Engine.h"

namespace Forge
{

    DirectionalLight::DirectionalLight()
    {}


    DirectionalLight::~DirectionalLight()
    {}


    void DirectionalLight::OnEnable()
    {
        engine->GetRenderer()->AddLight(this);
    }

    void DirectionalLight::OnDisable()
    {
        engine->GetRenderer()->RemoveLight(this);
    }

    const Color& DirectionalLight::GetColor() const
    {
        return _color;
    }

    void DirectionalLight::SetColor(const Color& color)
    {
        _color = color;
    }

    const Vector3& DirectionalLight::Direction() const
    {
        return _direction;
    }

    void DirectionalLight::Direction(const Vector3& direction)
    {
        _direction = direction;
    }
}
