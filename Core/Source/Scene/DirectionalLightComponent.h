#pragma once
#include "Graphics/DirectionalLight.h"
#include "Component.h"
#include "Graphics/Sprite.h"

namespace Forge
{

    class DirectionalLightComponent : public Component
    {
    private:
        DirectionalLight * directionalLight;
        Sprite* img;
    public:
        DirectionalLightComponent();
        ~DirectionalLightComponent();


        DirectionalLight* GetLight() const;
        void SetLight(DirectionalLight* directionalLight);

        void Update() override;

        void OnEnable() override;
        void OnDisable() override;
        void OnCreate() override;
    };

}
