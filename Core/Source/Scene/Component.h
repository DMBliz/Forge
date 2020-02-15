#pragma once
#include "Platform/Api/File.h"

namespace Forge
{
	class Entity;
	class Component
	{
		friend class ComponentManager;
	private:
		static uint gComponentID;

		static uint GetNextID()
		{
			return gComponentID++;
		}

		void SetComponentID(uint id)
		{
			if (gComponentID <= id)
				gComponentID = id + 1;
			componentID = id;
		}

		bool active = true;
		Entity* owner = nullptr;
	protected:
		uint componentID = GetNextID();
	public:
		Component()
		{}

		~Component()
		{}

		uint GetComponentID() const
		{
			return componentID;
		}

		bool IsActive() const { return active; }
		void SetActive(bool state);

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		virtual void OnCreate() { OnEnable(); }
		virtual void OnDestroy() { OnDisable(); }

		bool operator==(const Component& rhs) const
		{
			return componentID == rhs.componentID;
		}

		bool operator!=(const Component& rhs) const
		{
			return componentID != rhs.componentID;
		}

		virtual void Update(){}

		uint GetComponentID() { return componentID; }

		Entity* GetOwner() const { return owner; }
	};

}