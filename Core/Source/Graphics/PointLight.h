#pragma once
#include "Math/Matrix3x4.h"
#include "Math/Color.h"
#include "Utilities/ISwitchable.h"

namespace Forge
{

    class PointLight : public ISwitchable
    {
    private:
        const Matrix3x4* _transform;
        Color _color;
        float _linear;
        float _quadratic;
        bool active;
    public:
        PointLight();
        ~PointLight();

        void OnEnable() override;
        void OnDisable() override;

        const Color& GetColor() const;
        void SetColor(const Color& color);

        const Matrix3x4* GetTransform();
        void SetWorldTransform(const Matrix3x4& transform);

        float Linear() const;
        void Linear(float linear);

        float Quadratic() const;
        void Quadratic(float quadratic);

    };

}
