#include "Entity.h"
#include "Defines.h"
#include "ComponentManager.h"

namespace Forge
{
	uint Entity::gEntityID;
	void Entity::SetActive(bool state)
	{
		if (active == state)
			return;

		if (state)
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}

		active = state;
	}

    void Entity::OnDestroy()
    {
        for (Component* component : components)
        {
            component->OnDisable();
            component->OnDestroy();
        }
    }

	void Entity::Update()
	{
		for(Component* component : components)
		{
			component->Update();
		}
	}


	void Entity::DestroyAllComponents()
	{
		for (int i = 0; i < components.size(); i++)
		{
			_componentManager->DestroyComponent(components[i]);
		}
	}
}
