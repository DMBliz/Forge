#pragma once
#include <unordered_map>
#include "Containers/String.h"
#include "Defines.h"
#include "Types.h"
#include "EventSystem/Delegate.h"
#include <thread>
#include <mutex>
#include <queue>
#include "Resource.h"

namespace Forge
{
	class IResourceManager
	{
		virtual uint Count() const = 0;

		virtual void Update() = 0;
	};

	template<typename T>
	class ResourceManager : public IResourceManager
	{
	private:
		std::queue<std::pair<T*, Delegate<void(T*)>&>> addQueue;
		std::mutex queueLock;
		std::unordered_map<std::string, T*> resources;
		

		T* Load(String filename)
		{
			String name = filename.Trimmed().ToLower();

			auto it = resources.find(name.CString());
			
			if (it != resources.end())
			{
				
				resources[name.CString()]->IncReferences();

				return resources[name.CString()];
			}

			T* res = new T();
			res->Load(filename);

			res->IncReferences();

			return res;
		}
	public:
		ResourceManager(){}
		~ResourceManager(){}

		uint Count() const override
		{
			return resources.size();
		}

		void Update() override
		{
			while(addQueue.size() >= 1)
			{
				auto add = addQueue.back();
				//resources.insert(std::make_pair(add.first->GetResourceName(), add.first));
				/*if (add.second != nullptr)
					(*add.second)(add.first);*/
				addQueue.pop();
			}
		}

		T* GetLoaded(String filename)
		{
			auto it = resources.find(filename.CString());
			if(it != resources.end())
			{
				return resources[filename.CString()];
			}

			return nullptr;
		}

		void LoadAsync(String filename, Delegate<void(T*)>& onLoaded)
		{
			std::thread thread(&LoadMethod, filename, onLoaded);
		}

		void LoadMethod(String filename, Delegate<void(T*)>& onLoaded)
		{
			T* ret = Load(filename);

			std::unique_lock<std::mutex> lc(queueLock);

			lc.unlock();

			addQueue.push(std::make_pair(ret, onLoaded));

			lc.lock();
		}

		T* LoadResource(String filename)
		{
			T* res = Load(filename);
			resources.insert_or_assign(filename.CString(), res);
			return res;
		}

		bool Unload(String filename)
		{
			std::string name = filename.Trimmed().ToLower().CString();

			auto it = resources.find(name);

			if (it != resources.end())
			{
				resources[name]->DecReferences();

				if (resources[name]->GetReferenceCount() == 0)
				{
					delete (resources[name].second);
					resources.erase(it);
				}
				return true;
			}
			LOG("Cannot find resource with name:" + name);
			return false;
		}
	};
}
