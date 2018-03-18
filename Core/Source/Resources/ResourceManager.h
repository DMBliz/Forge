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
#include "Containers/String.h"
#include "Resources/Image.h"
#include "Graphics/Shader.h"

namespace Forge
{
	class IResourceManager
	{
	public:
		virtual uint Count() const = 0;

		virtual void Update() = 0;
	};

	template<typename T>
	class ResourceManager : public IResourceManager
	{
	private:
		std::queue<std::pair<T*, Delegate<void(T*)>*>> addQueue;
		std::mutex queueLock;
		std::unordered_map<std::string, T*> resources;
		
		static std::thread workers[10];
		static bool IsEnd[10];


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
				auto& add = addQueue.front();
				
				resources.insert(std::make_pair(add.first->GetResourceName().CString(), add.first));
				if (add.second != nullptr)
					(*add.second)(add.first);
				addQueue.pop();
			}
		}

		std::unordered_map<std::string, T*>* GetAll()
		{
			return &resources;
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

		void LoadAsync(String filename, Delegate<void(T*)>* onLoaded)
		{
			std::thread thread(&ResourceManager<T>::LoadMethod, this, filename, onLoaded);
			thread.join();
		}

		void LoadMethod(String filename, Delegate<void(T*)>* onLoaded)
		{
			T* ret = Load(filename);

			queueLock.lock();

			addQueue.push(std::pair<T*, Delegate<void(T*)>*>(ret, onLoaded));

			queueLock.unlock();
		}

		T* LoadResource(String filename)
		{
			auto* fn = resources[filename.CString()];
			if (fn == nullptr)
			{
				T* res = Load(filename);
				resources.insert_or_assign(filename.CString(), res);
				return res;
			}
			else
			{
				return fn;
			}
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
