#include "SpotLight.h"
#include "Core/Engine.h"

namespace Forge
{

    SpotLight::SpotLight()
    {}


    SpotLight::~SpotLight()
    {}


    void SpotLight::OnEnable()
    {
        engine->getRenderer()->AddLight(this);
    }

    void SpotLight::OnDisable()
    {
        engine->getRenderer()->RemoveLight(this);
    }

    const Matrix3x4* SpotLight::Transform() const
    {
        return _transform;
    }

    void SpotLight::Transform(const Matrix3x4& transform)
    {
        _transform = &transform;
    }

    Color SpotLight::GetColor() const
    {
        return _color;
    }

    void SpotLight::SetColor(const Color& color)
    {
        _color = color;
    }

    float SpotLight::Linear() const
    {
        return _linear;
    }

    void SpotLight::Linear(float linear)
    {
        _linear = linear;
    }

    float SpotLight::Quadratic() const
    {
        return _quadratic;
    }

    void SpotLight::Quadratic(float quadratic)
    {
        _quadratic = quadratic;
    }


    float SpotLight::CutOff() const
    {
        return _cutOff;
    }

    void SpotLight::CutOff(float cutOff)
    {
        _cutOff = cutOff;
    }

    float SpotLight::OuterCutOff() const
    {
        return _outerCutOff;
    }

    void SpotLight::OuterCutOff(float outerCutOff)
    {
        _outerCutOff = outerCutOff;
    }
}
