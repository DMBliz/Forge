#include "PointLight.h"
#include "Core/Engine.h"

namespace Forge
{

    PointLight::PointLight()
    {}


    PointLight::~PointLight()
    {}

    void PointLight::OnEnable()
    {
        engine->GetRenderer()->AddLight(this);
    }

    void PointLight::OnDisable()
    {
        engine->GetRenderer()->RemoveLight(this);
    }

    const Color& PointLight::GetColor() const
    {
        return _color;
    }

    void PointLight::SetColor(const Color& color)
    {
        _color = color;
    }

    const Matrix3x4* PointLight::GetTransform()
    {
        return _transform;
    }

    void PointLight::SetWorldTransform(const Matrix3x4& transform)
    {
        _transform = &transform;
    }

    float PointLight::Linear() const
    {
        return _linear;
    }

    void PointLight::Linear(float linear)
    {
        _linear = linear;
    }

    float PointLight::Quadratic() const
    {
        return _quadratic;
    }

    void PointLight::Quadratic(float quadratic)
    {
        _quadratic = quadratic;
    }
}
