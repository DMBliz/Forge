#pragma once
#include <unordered_map>
#include <typeinfo>
#include "Entity.h"

namespace Forge
{

	class EntityManager final
	{
	private:
		class IEntityContainer
		{
		public:
			virtual void Destroy(uint id) = 0;
			virtual void Clear() = 0;
			virtual bool ContainsEntity(uint id) = 0;
		};
		template<class T>
		class EntityContainer : public IEntityContainer
		{
		private:
			std::unordered_map<uint, T*> content;
		public:
			Iterator<T> Begin()
			{
				return Iterator<T>(content.begin()._Ptr);
			}

			Iterator<T> End()
			{
				return Iterator<T>(content.end()._Ptr);
			}

			void Add(T* value)
			{
				content[value->entityID] = value;
			}

			void Destroy(T* value)
			{
				if (content[value->entityID] != nullptr)
				{
                    value->OnDisable();
                    value->OnDestroy();
					delete value;
					content.erase(value->entityID);
				}
			}

			void Destroy(uint id) override
			{
				if (content[id] != nullptr)
				{
					content[id]->OnDestroy();
					delete content[id];
					content.erase(id);
				}
			}

			void Clear() override
			{
				for (uint i = 0; i < content.size(); i++)
				{
					content[i]->DestroyAllComponents();
					content[i]->OnDestroy();
					delete content[i];
				}

				content.clear();
			}

			bool ContainsEntity(uint id)
			{
				if (content[id] != nullptr)
					return true;
				else
					return false;
			}
		};

		std::unordered_map<std::type_index, IEntityContainer*> componentRegistry;

	public:
		ComponentManager _componentManager;
		EntityManager()
		{}
		~EntityManager()
		{}

		template<class T>
		EntityContainer<T>* GetEntityContainer()
		{
			auto pair = componentRegistry.find(typeid(T));
			if (pair == componentRegistry.end())
			{
				EntityContainer<T>* ent = new EntityContainer<T>();
				componentRegistry.insert(std::make_pair<std::type_index, IEntityContainer*>(typeid(T), static_cast<IEntityContainer*>(ent)));
				return ent;
			}
			else
			{
				return static_cast<EntityContainer<T>*>(componentRegistry[typeid(T)]);
			}
		}

		template<class T>
		T* CreateEntity()
		{
			Entity* t = new T();
			t->_componentManager = &_componentManager;
			t->OnCreate();

			EntityContainer<T>* cc = GetEntityContainer<T>();
			cc->Add(t);

			return static_cast<T*>(t);
		}

		template<class T>
		void DestroyEntity(uint id)
		{
			EntityContainer<T>* cc = GetEntityContainer<T>();

			cc->Destroy(id);
		}

		template<class T>
		void DestroyEntity(T* entity)
		{
			EntityContainer<T>* cc = GetEntityContainer<T>();

			cc->Destroy(entity);
		}

		void DestroyEntity(Entity* entity)
		{
			for (auto it = componentRegistry.begin(); it != componentRegistry.end(); ++it)
			{

				if(it->second->ContainsEntity(entity->GetEntityID()))
				{
					it->second->Destroy(entity->GetEntityID());
					return;
				}
			}
		}

		template<class T>
		void DestroyAllEntitys()
		{
			EntityContainer<T>* cc = GetEntityContainer<T>();

			cc->Clear();
		}

		template<class T>
		Iterator<T> Begin()
		{
			return GetEntityContainer<T>()->Begin();
		}

		template<class T>
		Iterator<T> End()
		{
			return GetEntityContainer<T>()->End();
		}
	};

}
