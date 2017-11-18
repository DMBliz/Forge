#pragma once
#include "Math/Mathf.h"
#include "Containers/String.h"

namespace Forge
{
	class StringHash
	{
	private:
		unsigned value;
	public:
		StringHash();
		StringHash(const char* rhs);
		StringHash(const String& rhs);
		StringHash(const StringHash& rhs);
		explicit StringHash(unsigned value);

		StringHash& operator=(const StringHash& rhs);
		bool operator==(const StringHash& rhs) const;
		bool operator!=(const StringHash& rhs) const;
		operator bool() const;
		
		unsigned Value() const;
		unsigned ToHash() const;
		
		static unsigned Calculate(const char* str);
	};
}
