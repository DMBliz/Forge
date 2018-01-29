#pragma once
#include <vector>
#include "Scene/Entity.h"
#include "Serialization/Meta.h"
#include "Scene/EntityManager.h"

namespace Forge
{

	class Scene
	{
		friend auto meta::registerMembers<Scene>();
		EntityManager manager;
		std::vector<Entity*> entitys;
	public:
		Scene();
		~Scene();

		void AddEntity(Entity* en);

		template<typename T>
		T* CreateEntity()
		{
			T* t = manager.CreateEntity<T>();
			entitys.push_back(static_cast<Entity*>(t));
			return t;
		}


	};

}
