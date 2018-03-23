#include "PointLightComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Core/Engine.h"
namespace Forge
{

    PointLightComponent::PointLightComponent()
    {
        light = new PointLight();
        img = new Sprite();
        
    }

    PointLightComponent::~PointLightComponent()
    {
        delete light;
        delete img;
    }

    PointLight* PointLightComponent::GetLight()
    {
        return light;
    }

    void PointLightComponent::OnEnable()
    {
        engine->GetRenderer()->AddLight(light);
    }

    void PointLightComponent::OnDisable()
    {
        engine->GetRenderer()->RemoveLight(light);
    }

    void PointLightComponent::Update()
    {
        if(IsActive())
        {
            img->Draw();
        }
    }

    void PointLightComponent::OnCreate()
    {
        light->SetActive(true);
        img->SetTexture(engine->GetResources()->LoadNowResource<Texture2D>("Resources/light2.png"));
        img->SetActive(true);
        TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
        if (trn != nullptr)
        {
            light->SetWorldTransform(*trn->GetWorldTransform());
            img->SetWorldPosition(*trn->GetWorldTransform());

        }
    }
}
