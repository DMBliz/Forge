#include "String.h"
#include <cassert>
#include "Utilities/Utils.h"

namespace Forge
{

	const String String::Empty;

	String::String()
		: charBuffer(nullptr), length_(0), capacity_(0)
	{}

	String::String(const String& str)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		*this = str;
	}

	String::String(const char* str)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		*this = str;
	}

	String::String(char* str)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		*this = static_cast<const char*>(str);
	}

	String::String(const char* str, unsigned length)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
        resize(length);
        copyChars(charBuffer, str, length);
	}

	String::String(const wchar_t* str)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
        setUTF8FromWChar(str);
	}

	String::String(wchar_t* str)
		: length_(0), capacity_(0), charBuffer(nullptr)
	{
        setUTF8FromWChar(str);
	}

	String::String(const WString& str)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
        setUTF8FromWChar(str.cString());
	}

	String::String(int value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%d", value);
		*this = tmp;
	}

	String::String(short value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%d", value);
		*this = tmp;
	}

	String::String(long value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%ld", value);
		*this = tmp;
	}

	String::String(long long value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%lld", value);
		*this = tmp;
	}

	String::String(unsigned value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%u", value);
		*this = tmp;
	}

	String::String(unsigned short value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%u", value);
		*this = tmp;
	}

	String::String(unsigned long value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%lu", value);
		*this = tmp;
	}

	String::String(unsigned long long value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%llu", value);
		*this = tmp;
	}

	String::String(float value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%g", value);
		*this = tmp;
	}

	String::String(double value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf(tmp, "%.15g", value);
		*this = tmp;
	}

	String::String(bool value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
		if (value)
			*this = "true";
		else
			*this = "false";
	}

	String::String(char value)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
        resize(1);
		charBuffer[0] = value;
	}

	String::String(char value, int length)
		: charBuffer(nullptr), length_(0), capacity_(0)
	{
        resize(1);
		for (unsigned i = 0; i < length_; i++)
		{
			charBuffer[i] = value;
		}
	}

	String::~String()
	{
		if(capacity_)
			delete[] charBuffer;
	}


	String& String::operator=(const String& rhs)
	{
        resize(rhs.length_);
        copyChars(charBuffer, rhs.charBuffer, rhs.length_);

		return *this;
	}

	String& String::operator=(const char* rhs)
	{
		unsigned len = cStringLength(rhs);
        resize(len);
        copyChars(charBuffer, rhs, len);

		return *this;
	}

	String& String::operator+=(const String& rhs)
	{
		unsigned oldLength = length_;
        resize(length_ + rhs.length_);
        copyChars(charBuffer + oldLength, rhs.charBuffer, rhs.length_);

		return *this;
	}


	String& String::operator+=(const char* rhs)
	{
		unsigned oldLength = length_;
		unsigned rhsLength = cStringLength(rhs);
        resize(length_ + rhsLength);
        copyChars(charBuffer + oldLength, rhs, rhsLength);

		return *this;
	}

	String& String::operator+=(char rhs)
	{
        resize(length_ + 1);
		charBuffer[length_ - 1] = rhs;

		return  *this;
	}

	String& String::operator+=(int value)
	{
		return *this += String(value);
	}

	String& String::operator+=(short value)
	{
		return *this += String(value);
	}

	String& String::operator+=(long value)
	{
		return *this += String(value);
	}

	String& String::operator+=(long long value)
	{
		return *this += String(value);
	}

	String& String::operator+=(unsigned value)
	{
		return *this += String(value);
	}

	String& String::operator+=(unsigned short value)
	{
		return *this += String(value);
	}

	String& String::operator+=(unsigned long value)
	{
		return *this += String(value);
	}

	String& String::operator+=(unsigned long long value)
	{
		return *this += String(value);
	}

	String& String::operator+=(float value)
	{
		return *this += String(value);
	}

	String& String::operator+=(double value)
	{
		return *this += String(value);
	}

	String& String::operator+=(bool value)
	{
		return *this += String(value);
	}


	template<class T>
	String String::operator+=(const T& rhs)
	{
		return *this += rhs.ToString();
	}

	String String::operator+(const String& rhs) const
	{
		String ret;
        ret.resize(length_ + rhs.length_);
        copyChars(ret.charBuffer, charBuffer, length_);
        copyChars(ret.charBuffer + length_, rhs.charBuffer, rhs.length_);

		return ret;
	}

	String String::operator+(const char* rhs) const
	{
		String ret;
		unsigned rhsLength = cStringLength(rhs);

        ret.resize(length_ + rhsLength);
        copyChars(ret.charBuffer, charBuffer, length_);
        copyChars(ret.charBuffer + length_, rhs, rhsLength);

		return ret;
	}

	String operator+(const char* lhs, const String& rhs)
	{
		String ret(lhs);
		ret += rhs;
		return ret;
	}

	String operator+(const wchar_t* lhs, const String& rhs)
	{
		String ret(lhs);
		ret += rhs;
		return ret;
	}

	bool String::operator==(const String& rhs) const
	{
		if (rhs.charBuffer == nullptr && charBuffer == nullptr)
			return true;
		else if (rhs.charBuffer == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs.cString()) == 0;
	}

	bool String::operator!=(const String& rhs) const
	{
		if (rhs.charBuffer == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs.charBuffer == nullptr || charBuffer == nullptr)
			return true;

		return strcmp(cString(), rhs.cString()) != 0;
	}

	bool String::operator<(const String& rhs) const
	{
		if (rhs.charBuffer == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs.charBuffer == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs.cString()) < 0;
	}
	
	bool String::operator>(const String& rhs) const
	{
		if (rhs.charBuffer == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs.charBuffer == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs.cString()) > 0;
	}

	bool String::operator==(const char* rhs) const
	{
		if (rhs == nullptr && charBuffer == nullptr)
			return true;
		else if (rhs == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs) == 0;
	}

	bool String::operator!=(const char* rhs) const
	{
		if (rhs == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs == nullptr || charBuffer == nullptr)
			return true;

		return strcmp(cString(), rhs) != 0;
	}

	bool String::operator<(const char* rhs) const
	{
		if (rhs == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs) < 0;
	}

	bool String::operator>(const char* rhs) const
	{
		if (rhs == nullptr && charBuffer == nullptr)
			return false;
		else if (rhs == nullptr || charBuffer == nullptr)
			return false;

		return strcmp(cString(), rhs) > 0;
	}

	char& String::operator[](unsigned index)
	{
		assert(index < length_);
		return charBuffer[index];
	}

	const char& String::operator[](unsigned index) const
	{
		assert(index < length_);
		return charBuffer[index];
	}

	char& String::at(unsigned index)
	{
		assert(index < length_);
		return charBuffer[index];
	}

	const char& String::at(unsigned index) const
	{
		assert(index < length_);
		return charBuffer[index];
	}

	void String::replace(char oldChar, char newChar, bool caseSensetive /*= true*/)
	{
		if (caseSensetive)
		{
			for (unsigned i = 0; i < length_; i++)
			{
				if (charBuffer[i] == oldChar)
					charBuffer[i] = newChar;
			}
		}
		else
		{
			oldChar = static_cast<char>(tolower(oldChar));
			for (unsigned i = 0; i < length_; i++)
			{
				if (tolower(charBuffer[i]) == oldChar)
					charBuffer[i] = newChar;
			}
		}
	}

	void String::replace(const String& oldValue, const String& newValue, bool caseSensetive /*= true*/)
	{
		unsigned next = 0;

		while (next < length_)
		{
			unsigned pos = find(oldValue, next, caseSensetive);
			if (pos == NOTFOUND)
				break;
            replace(pos, oldValue.length_, newValue);
			next = pos + newValue.length_;
		}
	}

	void String::replace(unsigned pos, unsigned length, const String& newValue)
	{
		if (pos + length > length_)
			return;

        replace(pos, length, newValue.charBuffer, newValue.length_);
	}

	void String::replace(unsigned pos, unsigned length, const char* newValue)
	{
		if (pos + length > length_)
			return;

        replace(pos, length, newValue, cStringLength(newValue));
	}

	String String::replaced(char oldChar, char newChar, bool caseSensetive /*= true*/)
	{
		String ret(*this);
        ret.replace(oldChar, newChar, caseSensetive);
		return ret;
	}

	String String::replaced(const String& oldValue, const String& newValue, bool caseSensetive /*= true*/)
	{
		String ret(*this);
        ret.replace(oldValue, newValue, caseSensetive);
		return ret;
	}

	String& String::append(const String& str)
	{
		return *this += str;
	}

	String& String::append(const char* str)
	{
		return *this += str;
	}

	String& String::append(char c)
	{
		return *this += c;
	}

	String& String::append(const char* str, unsigned length)
	{
		if (str)
		{
			unsigned oldLength = length_;
            resize(oldLength + length);
            copyChars(&charBuffer[oldLength], str, length);
		}
		return *this;
	}

	void String::insert(unsigned pos, const String& str)
	{
		if (pos > length_)
			pos = length_;

		if (pos == length_)
			*this += str;
		else
            replace(pos, 0, str);
	}

	void String::insert(unsigned pos, char c)
	{
		if (pos > length_)
			pos = length_;

		if (pos == length_)
			*this += c;
		else
		{
			unsigned oldLength = length_;
            resize(length_ + 1);
            moveRange(pos + 1, pos, oldLength - pos);
			charBuffer[pos] = c;
		}
	}

	void String::erase(unsigned pos, unsigned length /*= 1*/)
	{
        replace(pos, length, String::Empty);
	}

	void String::resize(unsigned newLength)
	{
		if (!capacity_)
		{
			if (!newLength)
				return;

			capacity_ = newLength + 1;
			if (capacity_ < MIN_CAPACITY)
				capacity_ = MIN_CAPACITY;

			charBuffer = new char[capacity_];
		}
		else
		{
			if (newLength < newLength + 1)
			{

				while (capacity_ < newLength + 1)
					capacity_ += capacity_ / 2;

				char* newBuffer = new char[capacity_];

				if (length_)
                    copyChars(newBuffer, charBuffer, length_);
				delete[] charBuffer;

				charBuffer = newBuffer;
			}
		}

		charBuffer[newLength] = 0;
		length_ = newLength;
	}

	void String::reserve(unsigned newCapacity)
	{
		if (newCapacity < length_ + 1)
			newCapacity = length_ + 1;
		if (newCapacity = capacity_)
			return;

		char* newBuffer = new char[newCapacity];

        copyChars(newBuffer, charBuffer, length_ + 1);
		if (capacity_)
			delete[] charBuffer;

		capacity_ = newCapacity;
		charBuffer = newBuffer;
	}

	void String::compact()
	{
		if (capacity_)
            reserve(length_ + 1);
	}

	void String::clear()
	{
        resize(0);
	}

	void String::swap(String& str)
	{
		Forge::Swap(length_, str.length_);
		Forge::Swap(capacity_, str.capacity_);
		Forge::Swap(charBuffer, str.charBuffer);
	}

	String String::subString(unsigned pos) const
	{
		if (pos < length_)
		{
			String ret;
            ret.resize(length_ - pos);
            copyChars(ret.charBuffer, charBuffer + pos, ret.length_);

			return ret;
		}
		else
			return String();
	}

	String String::subString(unsigned pos, unsigned length) const
	{
		if (pos < length_)
		{
			String ret;

			if (pos + length > length_)
				length = length_ - pos;

            ret.resize(length);
            copyChars(ret.charBuffer, charBuffer + pos, ret.length_);

			return ret;
		}
		else
			return String();
	}

	String String::trimmed() const
	{
		unsigned start = 0;
		unsigned end = length_;

		while (start < end)
		{
			char c = charBuffer[start];
			if (c != ' ')
				break;
			++start;
		}

		while (end > start)
		{
			char c = charBuffer[end];
			if (c != ' ')
				break;
			--end;
		}

		return subString(start, end);
	}

	String String::toUpper() const
	{
		String ret(*this);

		for (unsigned i = 0; i < ret.length_; i++)
			ret[i] = static_cast<char>(toupper(ret[i]));

		return ret;
	}

	String String::toLower() const
	{
		String ret(*this);

		for (unsigned i = 0; i < ret.length_; i++)
			ret[i] = static_cast<char>(tolower(ret[i]));

		return ret;
	}

	std::vector<String> String::split(char separator, bool keepEmptyStrings /*= false*/) const
	{
		return split(cString(), separator, keepEmptyStrings);
	}

	void String::join(const std::vector<String>& subStrings, const String& glue)
	{
		*this = joined(subStrings, glue);
	}

	unsigned String::find(char c, unsigned startInd /*= 0*/, bool caseSensetive /*= true*/) const
	{
		if (caseSensetive)
		{
			for (unsigned i = startInd; i < length_; ++i)
			{
				if (charBuffer[i] == c)
					return i;
			}
		}
		else
		{
			c = static_cast<char>(tolower(c));
			for (unsigned i = startInd; i < length_; ++i)
			{
				if (tolower(charBuffer[i]) == c)
					return i;
			}
		}

		return NOTFOUND;
	}

	unsigned String::find(const String& str, unsigned startInd /*= 0*/, bool caseSensetive /*= true*/) const
	{
		if (!str.length_ || str.length_ > length_)
			return NOTFOUND;

		char first = str.charBuffer[0];
		if (!caseSensetive)
			first = static_cast<char>(tolower(first));

		for (unsigned i = startInd; i <= length_ - str.length_; ++i)
		{
			char c = charBuffer[i];
			if (!caseSensetive)
				c = static_cast<char>(tolower(c));

			if (c == first)
			{
				unsigned skip = NOTFOUND;
				bool found = true;

				for (unsigned j = 1; j < str.length_; ++j)
				{
					c = charBuffer[i + j];
					char d = str.charBuffer[j];

					if (!caseSensetive)
					{
						c = static_cast<char>(tolower(c));
						d = static_cast<char>(tolower(d));
					}

					if (skip == NOTFOUND && c == first)
						skip = i + j - 1;

					if (c != d)
					{
						found = false;
						if (skip != NOTFOUND)
							i = skip;
						break;
					}
				}
				if (found)
					return i;
			}
		}

		return NOTFOUND;
	}

	unsigned String::findLast(char c, unsigned startInd, bool caseSensetive /*= true*/) const
	{
		if (startInd >= length_)
			startInd = length_ - 1;

		if (caseSensetive)
		{
			for (unsigned i = startInd; i < length_; --i)
			{
				if (charBuffer[i] == c)
					return i;
			}
		}
		else
		{
			c = static_cast<char>(tolower(c));
			for (unsigned i = startInd; i < length_; --i)
			{
				if (tolower(charBuffer[i]) == c)
					return i;
			}
		}

		return NOTFOUND;
	}

	unsigned String::findLast(const String& str, unsigned startInd, bool caseSensetive /*= true*/) const
	{
		if (!str.length_ || str.length_ > length_)
			return NOTFOUND;
		if (startInd > length_ - str.length_)
			startInd = length_ - str.length_;

		char first = str.charBuffer[0];
		if (!caseSensetive)
			first = static_cast<char>(tolower(first));

		for (unsigned i = startInd; i < length_ - str.length_; --i)
		{
			char c = charBuffer[i];
			if (!caseSensetive)
				c = static_cast<char>(tolower(c));

			if (c == first)
			{
				bool found = true;

				for (unsigned j = 1; j < str.length_; ++j)
				{
					c = charBuffer[j + 1];
					char d = str.charBuffer[j];

					if (!caseSensetive)
					{
						c = static_cast<char>(tolower(c));
						d = static_cast<char>(tolower(d));
					}

					if (c != d)
					{
						found = false;
						break;
					}
				}
				if (found)
					return i;
			}
		}

		return NOTFOUND;
	}

	bool String::startsWith(const String& str, bool caseSensetive /*= true*/) const
	{
		return find(str, 0, caseSensetive) == 0;
	}

	bool String::endsWith(const String& str, bool caseSensetive /*= true*/) const
	{
		unsigned pos = findLast(str, length_ - 1, caseSensetive);
		return pos != NOTFOUND && pos == length_ - str.length_;
	}

	int String::compare(const String& str, bool caseSensetive /*= true*/) const
	{
		return compare(cString(), str.cString(), caseSensetive);
	}

	int String::compare(const char* str, bool caseSensetive /*= true*/) const
	{
		return compare(cString(), str, caseSensetive);
	}

	bool String::contains(const String& str, bool caseSensetive /*= true*/) const
	{
		return find(str, 0, caseSensetive) != NOTFOUND;
	}

	bool String::contains(char c, bool caseSensetive /*= true*/) const
	{
		return find(c, 0, caseSensetive) != NOTFOUND;
	}

	void String::setUTF8FromChar(const char* str)
	{
		char temp[7];

        clear();

		if (!str)
			return;

		while (*str)
		{
			char* dest = temp;

            encodeUTF8(dest, static_cast<unsigned>(*str++));
			*dest = 0;
            append(temp);
		}
	}

	void String::setUTF8FromWChar(const wchar_t* str)
	{
		char temp[7];

        clear();

		if (!str)
			return;

#ifdef WIN32
		while (*str)
		{
			unsigned unicodeChar = DecodeUTF16(str);
			char* dest = temp;
			EncodeUTF8(dest, unicodeChar);
			*dest = 0;
			Append(temp);
		}
#else
		while (*str)
		{
			char* dest = temp;
            encodeUTF8(dest, (unsigned)*str++);
			*dest = 0;
            append(temp);
		}
#endif // WIN32
	}

	unsigned String::lengthUTF8() const
	{
		unsigned ret = 0;

		const char* src = charBuffer;
		if (!src)
			return ret;

		const char* end = charBuffer + length_;

		while (src < end)
		{
            decodeUTF8(src);
			++ret;
		}

		return ret;
	}

	unsigned String::byteOffsetUTF8(unsigned index) const
	{
		unsigned offset = 0;
		unsigned utfPos = 0;

		while (utfPos < index && offset < length_)
		{
            nextUTF8Char(offset);
			++utfPos;
		}

		return offset;
	}

	unsigned String::nextUTF8Char(unsigned& byteOffset) const
	{
		if (!charBuffer)
			return 0;

		const char* src = charBuffer + byteOffset;
		unsigned ret = decodeUTF8(src);
		byteOffset = static_cast<unsigned>(src - charBuffer);

		return ret;
	}

	unsigned String::atUTF8(unsigned index) const
	{
		unsigned byteOffset = byteOffsetUTF8(index);
		return nextUTF8Char(byteOffset);
	}

	void String::replaceUTF8(unsigned index, unsigned uniChar)
	{
		unsigned utfPos = 0;
		unsigned offset = 0;

		while (utfPos < index && offset < length_)
		{
            nextUTF8Char(offset);
			++utfPos;
		}

		if (utfPos < index)
			return;

		unsigned begin = offset;
        nextUTF8Char(offset);

		char temp[7];
		char* dest = temp;
        encodeUTF8(dest, uniChar);
		*dest = 0;

        replace(begin, offset - begin, temp, static_cast<unsigned>(dest - temp));
	}

	String& String::appendUTF8(unsigned uniChar)
	{
		char temp[7];
		char* dest = temp;
        encodeUTF8(dest, uniChar);
		*dest = 0;

		return append(temp);
	}

	String String::subStringUTF8(unsigned pos) const
	{
		unsigned utfLength = lengthUTF8();
		unsigned offset = byteOffsetUTF8(pos);
		String ret;

		while (pos < utfLength)
		{
            ret.appendUTF8(nextUTF8Char(offset));
			++pos;
		}

		return ret;
	}

	String String::subStringUTF8(unsigned pos, unsigned length) const
	{
		unsigned utfLength = lengthUTF8();
		unsigned offset = byteOffsetUTF8(pos);
		unsigned end = pos + length;
		String ret;

		while (pos < end && pos < utfLength)
		{
            ret.appendUTF8(nextUTF8Char(offset));
			++pos;
		}

		return ret;
	}

	unsigned String::hash() const
	{
		unsigned hash = 0;
		const char* ptr = charBuffer;
		while (*ptr)
		{
			hash = *ptr + (hash << 6u) + (hash << 16u) - hash;
			++ptr;
		}

		return hash;
	}



	void String::moveRange(unsigned dest, unsigned src, unsigned count)
	{
		if (count)
			memmove(charBuffer + dest, charBuffer + src, count);
	}

	void String::copyChars(char* dest, const char* src, unsigned count)
	{
		char* end = dest + count;
		while (dest != end)
		{
			*dest = *src;
			++dest;
			++src;
		}
	}

	void String::replace(unsigned pos, unsigned length, const char* src, unsigned srcLength)
	{
		int delta = static_cast<int>(srcLength) - static_cast<int>(length);

		if (pos + length < length_)
		{
			if (delta < 0)
			{
                moveRange(pos + srcLength, pos + length, length_ - pos - length);
                resize(length_ + delta);
			}
			else if (delta > 0)
			{
                resize(length_ + delta);
                moveRange(pos + srcLength, pos + length, length_ - pos - length - delta);
			}
		}
		else
		{
            resize(length_ + delta);
		}

        copyChars(charBuffer + pos, src, srcLength);
	}

	std::vector<String> String::split(const char* str, char separator, bool keepEmptyStrings /*= false*/)
	{
		std::vector<String> ret;
		const char* strEnd = str + String::cStringLength(str);

		for (const char* splitEnd = str; splitEnd != strEnd; ++splitEnd)
		{
			if (*splitEnd == separator)
			{
				const int splitLen = splitEnd - str;
				if (splitLen > 0 || keepEmptyStrings)
					ret.push_back(String(str, splitLen));
				str = splitEnd + 1;
			}
		}

		const int splintLen = strEnd - str;
		if (splintLen > 0 || keepEmptyStrings)
			ret.push_back(String(str, splintLen));

		return ret;
	}

	std::vector<String> String::split(const String& str, char separator, bool keepEmptyStrings /*= false*/)
	{
		return split(str.cString(), separator, keepEmptyStrings);
	}

	String String::joined(const std::vector<String>& subStrings, const String& glue)
	{
		if (subStrings.empty())
			return String();

		String joined(subStrings[0]);
		for (unsigned i = 1; i < subStrings.size(); ++i)
            joined.append(glue).append(subStrings[i]);

		return joined;
	}

	void String::encodeUTF8(char*& dest, unsigned uniChar)
	{
		if (uniChar < 0x80)
			*dest++ = uniChar;
		else if (uniChar < 0x800)
		{
			dest[0] = static_cast<char>(0xc0 | (uniChar >> 6) & 0x1f);
			dest[1] = static_cast<char>(0x80 | uniChar & 0x3f);
			dest += 2;
		}
		else if (uniChar < 0x10000)
		{
			dest[0] = static_cast<char>(0xe0 | (uniChar >> 12) & 0xf);
			dest[1] = static_cast<char>(0x80 | (uniChar >> 6) & 0x3f);
			dest[2] = static_cast<char>(0x80 | uniChar & 0x3f);
			dest += 3;
		}
		else if (uniChar < 0x200000)
		{
			dest[0] = static_cast<char>(0xf0 | (uniChar >> 18) & 0x7);
			dest[1] = static_cast<char>(0x80 | (uniChar >> 12) & 0x3f);
			dest[2] = static_cast<char>(0x80 | (uniChar >> 6) & 0x3f);
			dest[3] = static_cast<char>(0x80 | uniChar & 0x3f);
			dest += 4;

		}
		else if (uniChar < 0x4000000)
		{
			dest[0] = static_cast<char>(0xf8 | (uniChar >> 24) & 0x3);
			dest[1] = static_cast<char>(0x80 | (uniChar >> 18) & 0x3f);
			dest[2] = static_cast<char>(0x80 | (uniChar >> 12) & 0x3f);
			dest[3] = static_cast<char>(0x80 | (uniChar >> 6) & 0x3f);
			dest[4] = static_cast<char>(0x80 | uniChar & 0x3f);
			dest += 5;
		}
		else
		{
			dest[0] = static_cast<char>(0xfc | (uniChar >> 30) & 0x1);
			dest[1] = static_cast<char>(0x80 | (uniChar >> 24) & 0x3f);
			dest[2] = static_cast<char>(0x80 | (uniChar >> 18) & 0x3f);
			dest[3] = static_cast<char>(0x80 | (uniChar >> 12) & 0x3f);
			dest[4] = static_cast<char>(0x80 | (uniChar >> 6) & 0x3f);
			dest[5] = static_cast<char>(0x80 | uniChar & 0x3f);
			dest += 6;
		}
	}

	unsigned String::decodeUTF8(const char*& src)
	{
		if (src == nullptr)
			return 0;

		unsigned char char1 = *src++;

		if (char1 >= 0x80 && char1 < 0xc0)
		{
			while (static_cast<unsigned char>(*src) >= 0x80 && static_cast<unsigned char>(*src) < 0xc0)
				++src;
			return '?';
		}
		
		auto nextByte = [](const char*& src)
		{
			return (static_cast<unsigned char>(*src) < 0x80 || static_cast<unsigned char>(*src) >= 0xc0) ? ('?') : *(++src);
		};
		
		if (char1 < 0x80)
			return char1;
		else if (char1 < 0xe0)
		{
			unsigned char char2 = nextByte(src);
			return static_cast<unsigned>((char2 & 0x3f) | ((char1 & 0x1f) << 6));
		}
		else if (char1 < 0xf0)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			return static_cast<unsigned>((char3 & 0x3f) | ((char2 & 0x3f) << 6) | ((char1 & 0xf) << 12));
		}
		else if (char1 < 0xf8)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			return static_cast<unsigned>((char4 & 0x3f) | ((char3 & 0x3f) << 6) | ((char2 & 0x3f) << 12) | ((char1 & 0x7) << 18));
		}
		else if (char1 < 0xfc)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			unsigned char char5 = nextByte(src);
			return static_cast<unsigned>((char5 & 0x3f) | ((char4 & 0x3f) << 6) | ((char3 & 0x3f) << 12) | ((char2 & 0x3f) << 18) | (
											(char1 & 0x3) << 24));
		}
		else
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			unsigned char char5 = nextByte(src);
			unsigned char char6 = nextByte(src);
			return static_cast<unsigned>((char6 & 0x3f) | ((char5 & 0x3f) << 6) | ((char4 & 0x3f) << 12) | ((char3 & 0x3f) << 18) | (
											(char2 & 0x3f) << 24) | ((char1 & 0x1) << 30));
		}
	}

#ifdef WIN32
	void String::EncodeUTF16(wchar_t*& dest, unsigned uniChar)
	{
		if (uniChar < 0x10000)
			*dest++ = uniChar;
		else
		{
			uniChar -= 0x10000;
			*dest++ = 0xd800 | ((uniChar >> 18) & 0x3ff);
			*dest++ = 0xdc00 | (uniChar & 0x3ff);
		}
	}

	unsigned String::DecodeUTF16(const wchar_t*& src)
	{
		if (src == nullptr)
			return 0;

		unsigned short word1 = *src++;

		if (word1 >= 0xdc00 && word1 < 0xe000)
		{
			while (*src >= 0xdc00 && *src < 0xe000)
				++src;
			return '?';
		}

		if (word1 < 0xd800 || word1 >= 0xe000)
			return word1;
		else
		{
			unsigned char word2 = *src++;
			if (word2 < 0xdc00 || word2 >= 0xe000)
			{
				--src;
				return '?';
			}
			else
				return (((word1 & 0x3ff) << 10) | (word2 & 0x3ff)) + 0x10000;
		}
	}
#endif

	unsigned String::cStringLength(const char* str)
	{
		return str ? static_cast<unsigned>(strlen(str)) : 0;
	}

	int String::compare(const char* str1, const char* str2, bool caseSensetive /*= true*/)
	{
		if (!str1 || !str2)
			return str1 ? 1 : (str2 ? -1 : 0);

		if (caseSensetive)
			return strcmp(str1, str2);
		else
		{
			while(true)
			{
				char l = static_cast<char>(tolower(*str1));
				char r = static_cast<char>(tolower(*str2));
				if (!l || !r)
					return l ? 1 : (r ? -1 : 0);
				if (l < r)
					return -1;
				if (l > r)
					return 1;

				++str1;
				++str2;
			}
		}
	}

	int String::compare(const String& str1, const String& str2, bool caseSensetive /*= true*/)
	{
		return compare(str1.cString(), str2.cString(), caseSensetive);
	}

	WString::WString()
		: length_(0), wcharBuffer(nullptr)
	{}

	WString::WString(const String& str)
		: length_(0), wcharBuffer(nullptr)
	{

#ifdef WIN32
		unsigned neededSize = 0;
		wchar_t temp[3];

		unsigned offset = 0;
		while (offset < str.Length())
		{
			wchar_t* dest = temp;
			String::EncodeUTF16(dest, str.NextUTF8Char(offset));
			neededSize += dest - temp;
		}

		Resize(neededSize);

		offset = 0;
		wchar_t* dest = wcharBuffer;
		while (offset < str.Length())
			String::EncodeUTF16(dest, str.NextUTF8Char(offset));
#else
        resize(str.lengthUTF8());

		unsigned offset = 0;
		wchar_t* dest = wcharBuffer;
		while (offset < str.length())
			*dest++ = (wchar_t)str.nextUTF8Char(offset);
#endif
	}

	WString::~WString()
	{
		delete[] wcharBuffer;
	}

	wchar_t& WString::operator[](unsigned index)
	{
		assert(index < length_);
		return wcharBuffer[index];
	}

	const wchar_t& WString::operator[](unsigned index) const
	{
		assert(index < length_);
		return wcharBuffer[index];
	}

	wchar_t& WString::at(unsigned index)
	{
		assert(index < length_);
		return wcharBuffer[index];
	}

	const wchar_t& WString::at(unsigned index) const
	{
		assert(index < length_);
		return wcharBuffer[index];
	}

	void WString::resize(unsigned newLength)
	{
		if (!newLength)
		{
			delete[] wcharBuffer;
			wcharBuffer = nullptr;
			length_ = 0;
		}
		else
		{
			wchar_t* newBuffer = new wchar_t[newLength + 1];
			if (wcharBuffer)
			{
				unsigned copyLength = length_ < newLength ? length_ : newLength;
				memcpy(newBuffer, wcharBuffer, copyLength * sizeof(wchar_t));
				delete[] wcharBuffer;
			}

			newBuffer[newLength] = 0;
            wcharBuffer = newBuffer;
			length_ = newLength;
		}
	}
}
