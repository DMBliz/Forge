#pragma once
#include <vector>
#include "Component.h"
#include "ComponentManager.h"
#include "Defines.h"

namespace Forge
{

	class Entity
	{
		friend class EntityManager;
	private:
		ComponentManager* _componentManager;

		static const uint GetNextID()
		{
			static uint ComponentID = 0;
			return ComponentID++;
		}
		const uint entityID = GetNextID();
		bool active = true;
	protected:
		std::vector<Component*> components;
	public:
		Entity();
		virtual ~Entity();

		template<class T>
		void AddComponent()
		{
			Component* c = _componentManager->CreateComponent<T>(this);

			if (c)
			{
				components.push_back(c);
			}
			else
			{
				LOG("Wrong type passed");
			}
		}

		template<typename T>
		T* GetComponent()
		{
			for (int i = 0; i < components.size(); i++)
			{
				if (typeid(*components[i]) == typeid(T))
					return static_cast<T*>(components[i]);
			}

			return nullptr;
		}

		template <class T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> retComps;
			for (int i = 0; i < components.size(); i++)
			{
				if (typeid(*components[i]) == typeid(T))
					retComps.push_back(components[i]);
			}

			return retComps;
		}

		std::vector<Component*>& GetAllComponents()
		{
			return components;
		}

		template <class T>
		void DestroyComponent()
		{
			Component* c = GetComponent<T>();

			if (c)
			{
				_componentManager->DestroyComponent<T>(c->GetComponentID());
			}
			else
			{
				LOG("Wrong component type in destroyComponent");
			}
		}

		template <class T>
		void DestroyComponents()
		{
			std::vector<T*> Comps = GetComponents<T>();

			for (int i = 0; i < Comps.size(); i++)
			{
				_componentManager->DestroyComponent<T>(Comps[i]->GetComponentID());
			}
		}

		void DestroyAllComponents();

		bool IsActive() const { return active; }
		void SetActive(bool state);

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		virtual void OnCreate() {}
		virtual void OnDestroy() {}
	};
	
}
