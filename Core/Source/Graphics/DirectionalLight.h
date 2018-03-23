#pragma once
#include "Math/Color.h"
#include "Math/Vector3.h"
#include "Utilities/ISwitchable.h"

namespace Forge
{

    class DirectionalLight : public ISwitchable
    {
    private:
        Color _color;
        Vector3 _direction;
        bool active;
    public:
        DirectionalLight();
        ~DirectionalLight();

        void OnEnable() override;
        void OnDisable() override;

        const Color& GetColor() const;
        void SetColor(const Color& color);

        const Vector3& Direction() const;
        void Direction(const Vector3& direction);
    };

}
