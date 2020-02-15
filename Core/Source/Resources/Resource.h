#pragma once
#include "Containers/String.h"
#include "Types.h"

namespace Forge
{

	class Resource
	{
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

		virtual void Load(const String& filename);
		virtual void UnLoad();

		int GetReferenceCount() const;
		const String& GetResourceName() const;
	};	
}