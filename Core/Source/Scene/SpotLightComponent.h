#pragma once
#include "Graphics/SpotLight.h"
#include "Component.h"
#include "Graphics/Sprite.h"

namespace Forge
{

    class SpotLightComponent : public Component
    {
    private: 
        SpotLight * spotLight;
        Sprite* img;
    public:
        SpotLightComponent();
        ~SpotLightComponent();

        SpotLight* GetLight() const;
        void SetLight(SpotLight* spotLight);

        void Update() override;

        void OnEnable() override;
        void OnDisable() override;
        void OnCreate() override;
    };

}
