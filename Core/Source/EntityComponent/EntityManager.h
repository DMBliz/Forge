#pragma once
#include <unordered_map>
#include <typeinfo>
#include "Entity.h"

namespace Forge
{

	class EntityManager final
	{
	private:
		class IEntityContainer {};
		template<class T>
		class EntityContainer : public IEntityContainer
		{
		private:
			std::vector<T*> content;
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
				content.push_back(value);
			}

			void Destroy(T* value)
			{
				auto it = std::find(content.begin(), content.begin(), value);

				if (it != content.end())
				{
					value->OnDestroy();
					delete value;
					content.erase(it);
				}

			}

			void Destroy(uint id)
			{
				uint arrayID = 0;

				for (uint i = 0; i < content.size(); i++)
				{
					if (content[i]->componentID == id)
					{
						arrayID = i;
						break;
					}
				}

				content[arrayID]->OnDestroy();
				delete content[arrayID];
				content.erase(content.begin() + arrayID);
			}

			void Clear()
			{
				for (uint i = 0; i < content.size(); i++)
				{
					content[i]->DestroyAllComponents();
					content[i]->OnDestroy();
					delete content[i];
				}

				content.clear();
			}
		};

		std::unordered_map<std::type_index, IEntityContainer*> componentRegistry;

	public:
		ComponentManager* _componentManager;
		EntityManager();
		~EntityManager();

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
			t->_componentManager = _componentManager;
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
		void DestroyEntity(T* component)
		{
			EntityContainer<T>* cc = GetEntityContainer<T>();

			cc->Destroy(component);
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
