#include "SpotLightComponent.h"
#include "TransformComponent.h"
#include "Core/Engine.h"
namespace Forge
{

    SpotLightComponent::SpotLightComponent()
    {
        spotLight = new SpotLight();
        img = new Sprite();
    }


    SpotLightComponent::~SpotLightComponent()
    {}

    SpotLight* SpotLightComponent::GetLight() const
    {
        return spotLight;
    }

    void SpotLightComponent::SetLight(SpotLight* spotLight)
    {
        this->spotLight = spotLight;
    }


    void SpotLightComponent::Update()
    {
        if (IsActive())
        {
            img->Draw();
        }
    }

    void SpotLightComponent::OnEnable()
    {
        engine->GetRenderer()->AddLight(spotLight);
    }

    void SpotLightComponent::OnDisable()
    {
        engine->GetRenderer()->RemoveLight(spotLight);
    }

    void SpotLightComponent::OnCreate()
    {
        spotLight->SetActive(true);
        img->SetTexture(engine->GetResources()->LoadNowResource<Texture2D>("Resources/light2.png"));
        img->SetActive(true);
        TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
        if (trn != nullptr)
        {
            spotLight->Transform(*trn->GetWorldTransform());
            img->SetWorldPosition(*trn->GetWorldTransform());

        }
    }
}
