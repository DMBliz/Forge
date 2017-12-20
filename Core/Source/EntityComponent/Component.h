#pragma once
#include "FileSystem/File.h"

namespace Forge
{
	class Entity;
	class Component
	{
		friend class ComponentManager;

	private:
		static const uint GetNextID()
		{
			static uint ComponentID = 0;
			return ComponentID++;
		}
		bool active = true;
		Entity* owner = nullptr;
	protected:
		const uint componentID = GetNextID();
	public:
		Component()
		{}

		~Component()
		{}

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

		uint GetComponentID() { return componentID; }

		Entity* GetOwner() const { return owner; }
	};

}
