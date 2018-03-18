#pragma once
#include <vector>
#include "Component.h"
#include "ComponentManager.h"
#include "Defines.h"
#include "Serialization/meta.h"
#include "TransformComponent.h"

namespace Forge
{

	class Entity
	{
		friend class EntityManager;
		friend inline auto meta::registerMembers<Entity>();
	private:
		ComponentManager* _componentManager;
		
		static uint gEntityID;

		static uint GetNextID()
		{
			return gEntityID++;
		}
		uint entityID = GetNextID();

		void SetEntityID(uint id)
		{
			if (gEntityID <= id)
				gEntityID = id + 1;
			entityID = id;
		}

		bool active = true;

		void SetComponents(const std::vector<Component*>& newComponents)
		{
			components.clear();
			components.push_back(*newComponents.data());
		}

		void AddChild(Entity* child)
		{
			auto it = std::find(childs.begin(), childs.end(), child);
			if(it == childs.end())
				childs.push_back(child);

            TransformComponent* childTransform = child->GetComponent<TransformComponent>();
            TransformComponent* transform = GetComponent<TransformComponent>();

            if (childTransform != nullptr && transform != nullptr)
            {
                childTransform->Parent(transform);
            }
		}

		String name;

	protected:

		void RemoveChild(Entity* child)
		{
			for (auto i = childs.begin(); i != childs.end(); ++i)
			{
				if (child->GetEntityID() == (*i)->GetEntityID())
				{
					childs.erase(i);

                    TransformComponent* childTransform = child->GetComponent<TransformComponent>();
                    TransformComponent* transform = GetComponent<TransformComponent>();

                    if (childTransform != nullptr && transform != nullptr)
                    {
                        childTransform->Parent(nullptr);
                    }
					return;
				}
			}
		}
		std::vector<Component*> components;
		std::vector<Entity*> childs;
		Entity* parent = nullptr;
	public:
		Entity()
		{}
		virtual ~Entity()
		{}

		uint GetEntityID() const
		{
			return entityID;
		}

		const String& Name() const
		{
			return name;
		}

		void Name(const String& newName)
		{
			name = newName;
		}

		virtual void SetParent(Entity* newParent)
		{
			if (parent != nullptr)
				parent->RemoveChild(this);
			parent = newParent;
			newParent->AddChild(this);
		}

		template<class T>
		T* AddComponent()
		{
			Component* c = _componentManager->CreateComponent<T>(this);

			if (c)
			{
				components.push_back(c);

                if(typeid(T) == typeid(TransformComponent) && parent != nullptr)
                {
                    TransformComponent* ptr = parent->GetComponent<TransformComponent>();
                    if(ptr != nullptr)
                    {
                        static_cast<TransformComponent*>(c)->Parent(ptr);
                    }
                }

				return static_cast<T*>(c);
			}
			else
			{
				LOG("Wrong type passed");
				return nullptr;
			}
		}

		template<typename T>
		T* GetComponent()
		{
			for (uint i = 0; i < components.size(); i++)
			{
				if (typeid(*components[i]) == typeid(T))
					return static_cast<T*>(components[i]);
			}

			return nullptr;
		}

		template <class T>
		const std::vector<T*>& GetComponents()
		{
			std::vector<T*> retComps;
			for (int i = 0; i < components.size(); i++)
			{
				if (typeid(*components[i]) == typeid(T))
					retComps.push_back(components[i]);
			}

			return retComps;
		}

		const std::vector<Component*>& GetAllComponents() const
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

		const std::vector<Entity*>& GetAllChilds() const
		{
			return childs;
		}

		uint GetChildsCount() const 
		{
			return childs.size();
		}

		void DestroyAllComponents();

		bool IsActive() const { return active; }
		void SetActive(bool state);

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		virtual void OnCreate() {}
		virtual void OnDestroy() {}

		virtual void Update();
	};
}


namespace meta
{
	template<>
	inline auto registerMembers<Forge::Entity>()
	{
		return members(
			member("EntityID", &Forge::Entity::GetEntityID, &Forge::Entity::SetEntityID),
			member("Components", &Forge::Entity::GetAllComponents, &Forge::Entity::SetComponents)
		);
	}
}
