#include "DirectionalLightComponent.h"
#include "TransformComponent.h"
#include "Core/Engine.h"

namespace Forge
{

    DirectionalLightComponent::DirectionalLightComponent()
    {
        directionalLight = new DirectionalLight();
        img = new Sprite();
    }


    DirectionalLightComponent::~DirectionalLightComponent()
    {}

    DirectionalLight* DirectionalLightComponent::GetLight() const
    {
        return directionalLight;
    }

    void DirectionalLightComponent::SetLight(DirectionalLight* directionalLight)
    {
        this->directionalLight = directionalLight;
    }

    void DirectionalLightComponent::Update()
    {
        if (IsActive())
        {
            img->Draw();
        }
    }

    void DirectionalLightComponent::OnEnable()
    {
        engine->getRenderer()->AddLight(directionalLight);
    }

    void DirectionalLightComponent::OnDisable()
    {
        engine->getRenderer()->RemoveLight(directionalLight);
    }

    void DirectionalLightComponent::OnCreate()
    {
        directionalLight->SetActive(true);
        img->SetTexture(engine->getResources()->LoadNowResource<Texture2D>("Resources/light2.png"));
        img->SetActive(true);
        TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
        if (trn != nullptr)
        {
            img->SetWorldPosition(*trn->GetWorldTransform());
        }
    }
}
