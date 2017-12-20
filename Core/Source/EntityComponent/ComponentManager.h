#pragma once
#include <unordered_map>
#include <typeinfo>
#include "Component.h"
#include "Containers/Iterator.h"
#include "Types.h"
#include <algorithm>
#include <typeindex>

namespace Forge
{
	class Entity;
	class ComponentManager final
	{
	private:
		class IComponentContainer {};
		template<class T>
		class ComponentContainer : public IComponentContainer
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
					delete content[i];
				}

				content.clear();
			}
		};

		std::unordered_map<std::type_index, IComponentContainer*> componentRegistry;
	public:
		ComponentManager();
		~ComponentManager();

		template<class T>
		ComponentContainer<T>* GetComponentContainer()
		{
			auto pair = componentRegistry.find(typeid(T));
			if (pair == componentRegistry.end())
			{
				ComponentContainer<T>* cc = new ComponentContainer<T>();
				
				componentRegistry.insert(std::make_pair<std::type_index, IComponentContainer*>(typeid(T), static_cast<IComponentContainer*>(cc)));

				return cc;
			}
			else
			{
				return static_cast<ComponentContainer<T>*>(componentRegistry[typeid(T)]);
			}
		}

		template<class T>
		T* CreateComponent(Entity* owner)
		{
			Component* t = new T();
			t->owner = owner;
			t->OnCreate();

			ComponentContainer<T>* cc = GetComponentContainer<T>();
			cc->Add(static_cast<T*>(t));

			return static_cast<T*>(t);
		}

		template<class T>
		void DestroyComponent(uint id)
		{
			ComponentContainer<T>* cc = GetComponentContainer<T>();

			cc->Destroy(id);
		}

		template<class T>
		void DestroyComponent(T* component)
		{
			ComponentContainer<T>* cc = GetComponentContainer<T>();

			cc->Destroy(component);
		}

		template<class T>
		void DestroyAllComponents()
		{
			ComponentContainer<T>* cc = GetComponentContainer<T>();

			cc->Clear();
		}

		template<class T>
		Iterator<T> Begin()
		{
			return GetComponentContainer<T>()->Begin();
		}

		template<class T>
		Iterator<T> End()
		{
			return GetComponentContainer<T>()->End();
		}
	};

}
