#pragma once
#include "Graphics/PointLight.h"
#include "Graphics/Sprite.h"
#include "Scene/Component.h"

namespace Forge
{

    class PointLightComponent : public Component
    {
    private: 
        PointLight* light;
        Sprite* img;
    public:
        PointLightComponent();
        ~PointLightComponent();

        PointLight* GetLight();

        void OnEnable() override;
        void OnDisable() override;

        void Update() override;
        void OnCreate() override;
    };

}
