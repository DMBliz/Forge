#pragma once
#include "ResourceManager.h"
#include <typeindex>
#include "Resource.h"
#include "Serialization/meta.h"

namespace Forge
{

	class Resources
	{
		friend auto meta::registerMembers<Resources>();
	private:
		std::unordered_map<std::type_index, IResourceManager*> resources;
		std::vector<Resource*> res;
	public:
		static Resources* Singleton()
		{
			static Resources* singleton = new Resources();
			return singleton;
		}

		//TODO: refactor this
		template<typename T>
		void RegisterResource()
		{
			auto t = resources.find(typeid(T));
			if (t == resources.end() || t->second == nullptr)
				resources.insert_or_assign(typeid(T), new ResourceManager<T>());
		}

		template<typename T>
		T* GetResource(String filename)
		{
			std::type_index ti = typeid(T);
			IResourceManager* man = resources[ti];
			ResourceManager<T>* resm = static_cast<ResourceManager<T>*>(man);
			return resm->GetLoaded(filename);
		}

		template<typename T>
		T* LoadNowResource(String filename)
		{
			ResourceManager<T>* res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
			if (res != nullptr)
				return res->LoadResource(filename);
			else
			{
				RegisterResource<T>();
				res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
				return res->LoadResource(filename);
			}

			return nullptr;
		}

		template<typename T>
		void LoadResource(String filename)
		{
			ResourceManager<T>* res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
			if (res != nullptr)
				return res->LoadAsync(filename, nullptr);
			else
			{
				RegisterResource<T>();
				res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
				res->LoadAsync(filename, nullptr);
			}
		}
		
		template<typename T>
		void LoadResource(String filename, Delegate<void(T*)>& callback)
		{
			ResourceManager<T>* res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
			if (res != nullptr)
				return res->LoadAsync(filename, callback);
			else
			{
				RegisterResource<T>();
				res = static_cast<ResourceManager<T>*>(resources[typeid(T)]);
				res->LoadAsync(filename, callback);
			}
		}
	};
}


namespace meta
{
	template<>
	inline auto registerMembers<Forge::Resources>()
	{
		return members(
			member("Resources", &Forge::Resources::res)
		);
	}
}