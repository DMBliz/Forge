#pragma once
#include "Containers/String.h"
#include "Serialization/Meta.h"

namespace Forge
{

	class Resource
	{
		friend auto meta::registerMembers<Resource>();
		template<typename T> friend class ResourceManager;
	private:
		int referenceCount;
		void IncReferences();
		void DecReferences();
	protected:
		String resourceName;
	public:
		Resource();
		virtual ~Resource();

		virtual void Load(String filename);
		virtual void UnLoad();

		int GetReferenceCount() const;
		String GetResourceName() const;
	};	
}


namespace meta
{
	template<>
	inline auto registerMembers<Forge::Resource>()
	{
		return members(
			member("name", &Forge::Resource::resourceName)
		);
	}
}