#include "Resource.h"
#include "Defines.h"

namespace Forge
{
	void Resource::IncReferences()
	{
		referenceCount++;
	}

	void Resource::DecReferences()
	{
		referenceCount--;
		if(referenceCount <= 0)
		{
			UnLoad();
		}
	}

	Resource::Resource()
	{}

	Resource::~Resource()
	{}

	void Resource::Load(String filename)
	{
		if (filename.IsEmpty())
			LOG("filename cannot be empty");

		referenceCount = 0;
		resourceName = filename.Trimmed().ToLower();
	}

	void Resource::UnLoad()
	{
		referenceCount = 0;
		resourceName = String::Empty;
	}

	int Resource::GetReferenceCount() const
	{
		return referenceCount;
	}

	const String& Resource::GetResourceName() const
	{
		return resourceName;
	}
}
