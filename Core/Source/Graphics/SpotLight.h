#pragma once
#include "Math/Color.h"
#include "Math/Matrix3x4.h"
#include "Utilities/ISwitchable.h"

namespace Forge
{

    class SpotLight : public ISwitchable
    {
        const Matrix3x4* _transform;
        Color _color;
        float _linear;
        float _quadratic;
        float _cutOff;
        float _outerCutOff;
        bool active;
    public:
        SpotLight();
        ~SpotLight();

        void OnEnable() override;
        void OnDisable() override;

        const Matrix3x4* Transform() const;
        void Transform(const Matrix3x4& transform);

        Color GetColor() const;
        void SetColor(const Color& color);

        float Linear() const;
        void Linear(float linear);

        float Quadratic() const;
        void Quadratic(float quadratic);

        float CutOff() const;
        void CutOff(float cutOff);

        float OuterCutOff() const;
        void OuterCutOff(float outerCutOff);
    };

}
