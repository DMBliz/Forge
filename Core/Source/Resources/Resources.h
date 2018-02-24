#pragma once
#include "ResourceManager.h"
#include <typeindex>
#include "Resource.h"
#include "Serialization/meta.h"
#include "Graphics/Shader.h"
#include "EventSystem/Event.h"

namespace Forge
{

	class Resources
	{
		friend auto meta::registerMembers<Resources>();
	private:
		std::unordered_map<std::type_index, IResourceManager*> resources;
		std::vector<Resource*> res;
	public:

		void Update()
		{
			for(auto& res : resources)
			{
				res.second->Update();
			}
		}

		void LoadAll(const std::vector<String>& files)
		{
			for(const String& file : files)
			{
				if(file.Contains(".glsl"))
				{
					LoadResource<Shader>(file);
				}
				if (file.Contains(".jpg"))
				{
					LoadResource<Image>(file);
				}
				if (file.Contains(".png"))
				{
					LoadResource<Image>(file);
				}
			}
		}
		
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
		ResourceManager<T>* GetResourceManager()
		{
			return static_cast<ResourceManager<T>*>(resources[typeid(T)]);
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
		void LoadResource(String filename, Delegate<void(T*)>* callback)
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