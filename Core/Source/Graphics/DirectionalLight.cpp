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
        engine->getRenderer()->AddLight(this);
    }

    void DirectionalLight::OnDisable()
    {
        engine->getRenderer()->RemoveLight(this);
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
