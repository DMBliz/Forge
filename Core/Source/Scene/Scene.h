#pragma once
#include <vector>
#include "Scene/Entity.h"
#include "Scene/EntityManager.h"

namespace Forge
{

	class Scene : public Entity
	{
		EntityManager manager;

		void SetEntitys(const std::vector<Entity*>& newEntitys)
		{
			childs.clear();
			childs.push_back(*newEntitys.data());
		}

		void SetParent(Entity* newParent) override
		{}

	public:
		Scene();
		~Scene();

		template<typename T>
		T* CreateEntity()
		{
			T* t = manager.CreateEntity<T>();
			childs.push_back(static_cast<Entity*>(t));
			t->SetParent(this);
			return t;
		}

		template<typename T>
		T* CreateEntity(const String& name)
		{
			T* t = manager.CreateEntity<T>();
			childs.push_back(static_cast<Entity*>(t));
			t->SetParent(this);
			t->Name(name);
			return t;
		}

		template<typename T>
		void DestroyEntity(T* entity)
		{
			manager.DestroyEntity(entity);
			RemoveChild(entity);
		}

		void Update() override;
	};
}

