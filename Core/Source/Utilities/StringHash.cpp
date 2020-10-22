#include "StringHash.h"
#include <cctype>

namespace Forge
{
	StringHash::StringHash()
		: value(0)
	{}

	StringHash::StringHash(const char* rhs)
		: value(Calculate(rhs))
	{}

	StringHash::StringHash(const String& rhs)
		: value(Calculate(rhs.cString()))
	{}

	StringHash::StringHash(unsigned value)
		: value(value)
	{}

	StringHash::StringHash(const StringHash& rhs)
		: value(rhs.value)
	{}

	StringHash& StringHash::operator=(const StringHash& rhs)
	{
		value = rhs.value;

		return *this;
	}

	bool StringHash::operator==(const StringHash& rhs) const
	{
		return value == rhs.value;
	}

	bool StringHash::operator!=(const StringHash& rhs) const
	{
		return value != rhs.value;
	}

	StringHash::operator bool() const
	{
		return value != 0;
	}

	unsigned StringHash::Value() const
	{
		return value;
	}

	unsigned StringHash::ToHash() const
	{
		return value;
	}

	unsigned StringHash::Calculate(const char* str)
	{
		unsigned hash = 0;

		if (!str)
			return hash;

		while (*str)
		{
			char c = *str;
			hash = Forge::SDBMHash(hash, (unsigned char)std::tolower(c));
			++str;
		}

		return hash;
	}

}
