#include "String.h"
#include <cassert>
#include "Utilities/Utils.h"

namespace Forge
{

	const String String::Empty;

	String::String()
		: length_(0), capacity_(0), charBuffer(0)
	{}

	String::String(const String& str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		*this = str;
	}

	String::String(const char* str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		*this = str;
	}

	String::String(char* str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		*this = (const char*)str;
	}

	String::String(const char* str, unsigned length)
		: length_(0), capacity_(0), charBuffer(0)
	{
		Resize(length);
		CopyChars(charBuffer, str, length);
	}

	String::String(const wchar_t* str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		SetUTF8FromWChar(str);
	}

	String::String(wchar_t* str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		SetUTF8FromWChar(str);
	}

	String::String(const WString& str)
		: length_(0), capacity_(0), charBuffer(0)
	{
		SetUTF8FromWChar(str.CString());
	}

	String::String(int value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%d", value);
		*this = tmp;
	}

	String::String(short value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%d", value);
		*this = tmp;
	}

	String::String(long value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%ld", value);
		*this = tmp;
	}

	String::String(long long value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%lld", value);
		*this = tmp;
	}

	String::String(unsigned value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%u", value);
		*this = tmp;
	}

	String::String(unsigned short value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%u", value);
		*this = tmp;
	}

	String::String(unsigned long value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%lu", value);
		*this = tmp;
	}

	String::String(unsigned long long value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%llu", value);
		*this = tmp;
	}

	String::String(float value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%g", value);
		*this = tmp;
	}

	String::String(double value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		char tmp[CONVERSION_BUFFER_LENGTH];
		sprintf_s(tmp, "%.15g", value);
		*this = tmp;
	}

	String::String(bool value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		if (value)
			*this = "true";
		else
			*this = "false";
	}

	String::String(char value)
		: length_(0), capacity_(0), charBuffer(0)
	{
		Resize(1);
		charBuffer[0] = value;
	}

	String::String(char value, int length)
		: length_(0), capacity_(0), charBuffer(0)
	{
		Resize(1);
		for (unsigned i = 0; i < length_; i++)
		{
			charBuffer[i] = value;
		}
	}

	template<class T>
	Forge::String::String(const T& value)
		: length_(0), capacity_(0), str(0)
	{
		*this = value.ToString();
	}

	String::~String()
	{
		if(capacity_)
			delete[] charBuffer;
	}


	String& String::operator=(const String& rhs)
	{
		Resize(rhs.length_);
		CopyChars(charBuffer, rhs.charBuffer, rhs.length_);

		return *this;
	}

	String& String::operator=(const char* rhs)
	{
		unsigned len = CStringLength(rhs);
		Resize(len);
		CopyChars(charBuffer, rhs, len);

		return *this;
	}

	String& String::operator+=(const String& rhs)
	{
		unsigned oldLength = length_;
		Resize(length_ + rhs.length_);
		CopyChars(charBuffer + oldLength, rhs.charBuffer, rhs.length_);

		return *this;
	}


	String& String::operator+=(const char* rhs)
	{
		unsigned oldLength = length_;
		unsigned rhsLength = CStringLength(rhs);
		Resize(length_ + rhsLength);
		CopyChars(charBuffer + oldLength, rhs, rhsLength);

		return *this;
	}

	String& String::operator+=(char rhs)
	{
		Resize(length_ + 1);
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
		ret.Resize(length_ + rhs.length_);
		CopyChars(ret.charBuffer, charBuffer, length_);
		CopyChars(ret.charBuffer + length_, rhs.charBuffer, rhs.length_);

		return ret;
	}

	String String::operator+(const char* rhs) const
	{
		String ret;
		unsigned rhsLength = CStringLength(rhs);

		ret.Resize(length_ + rhsLength);
		CopyChars(ret.charBuffer, charBuffer, length_);
		CopyChars(ret.charBuffer + length_, rhs, rhsLength);

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
		return strcmp(CString(), rhs.CString()) == 0;
	}

	bool String::operator!=(const String& rhs) const
	{
		return strcmp(CString(), rhs.CString()) != 0;
	}

	bool String::operator<(const String& rhs) const
	{
		return strcmp(CString(), rhs.CString()) < 0;
	}
	
	bool String::operator>(const String& rhs) const
	{
		return strcmp(CString(), rhs.CString()) > 0;
	}

	bool String::operator==(const char* rhs) const
	{
		return strcmp(CString(), rhs) == 0;
	}

	bool String::operator!=(const char* rhs) const
	{
		return strcmp(CString(), rhs) != 0;
	}

	bool String::operator<(const char* rhs) const
	{
		return strcmp(CString(), rhs) < 0;
	}

	bool String::operator>(const char* rhs) const
	{
		return strcmp(CString(), rhs) > 0;
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

	char& String::At(unsigned index)
	{
		assert(index < length_);
		return charBuffer[index];
	}

	const char& String::At(unsigned index) const
	{
		assert(index < length_);
		return charBuffer[index];
	}

	void String::Replace(char oldChar, char newChar, bool caseSensetive /*= true*/)
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
			oldChar = (char)tolower(oldChar);
			for (unsigned i = 0; i < length_; i++)
			{
				if (tolower(charBuffer[i]) == oldChar)
					charBuffer[i] = newChar;
			}
		}
	}

	void String::Replace(const String& oldValue, const String& newValue, bool caseSensetive /*= true*/)
	{
		unsigned next = 0;

		while (next < length_)
		{
			unsigned pos = Find(oldValue, next, caseSensetive);
			if (pos == NOTFOUND)
				break;
			Replace(pos, oldValue.length_, newValue);
			next = pos + newValue.length_;
		}
	}

	void String::Replace(unsigned pos, unsigned length, const String& newValue)
	{
		if (pos + length > length_)
			return;

		Replace(pos, length, newValue.charBuffer, newValue.length_);
	}

	void String::Replace(unsigned pos, unsigned length, const char* newValue)
	{
		if (pos + length > length_)
			return;

		Replace(pos, length, newValue, CStringLength(newValue));
	}

	String String::Replaced(char oldChar, char newChar, bool caseSensetive /*= true*/)
	{
		String ret(*this);
		ret.Replace(oldChar, newChar, caseSensetive);
		return ret;
	}

	String String::Replaced(const String& oldValue, const String& newValue, bool caseSensetive /*= true*/)
	{
		String ret(*this);
		ret.Replace(oldValue, newValue, caseSensetive);
		return ret;
	}

	String& String::Append(const String& str)
	{
		return *this += str;
	}

	String& String::Append(const char* str)
	{
		return *this += str;
	}

	String& String::Append(char c)
	{
		return *this += c;
	}

	String& String::Append(const char* str, unsigned length)
	{
		if (str)
		{
			unsigned oldLength = length_;
			Resize(oldLength + length);
			CopyChars(&charBuffer[oldLength], str, length);
		}
		return *this;
	}

	void String::Insert(unsigned pos, const String& str)
	{
		if (pos > length_)
			pos = length_;

		if (pos == length_)
			*this += str;
		else
			Replace(pos, 0, str);
	}

	void String::Insert(unsigned pos, char c)
	{
		if (pos > length_)
			pos = length_;

		if (pos == length_)
			*this += c;
		else
		{
			unsigned oldLength = length_;
			Resize(length_ + 1);
			MoveRange(pos + 1, pos, oldLength - pos);
			charBuffer[pos] = c;
		}
	}

	void String::Erase(unsigned pos, unsigned length /*= 1*/)
	{
		Replace(pos, length, String::Empty);
	}

	void String::Resize(unsigned newLength)
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
					CopyChars(newBuffer, charBuffer, length_);
				delete[] charBuffer;

				charBuffer = newBuffer;
			}
		}

		charBuffer[newLength] = 0;
		length_ = newLength;
	}

	void String::Reserve(unsigned newCapacity)
	{
		if (newCapacity < length_ + 1)
			newCapacity = length_ + 1;
		if (newCapacity = capacity_)
			return;

		char* newBuffer = new char[newCapacity];

		CopyChars(newBuffer, charBuffer, length_ + 1);
		if (capacity_)
			delete[] charBuffer;

		capacity_ = newCapacity;
		charBuffer = newBuffer;
	}

	void String::Compact()
	{
		if (capacity_)
			Reserve(length_ + 1);
	}

	void String::Clear()
	{
		Resize(0);
	}

	void String::Swap(String& str)
	{
		Forge::Swap(length_, str.length_);
		Forge::Swap(capacity_, str.capacity_);
		Forge::Swap(charBuffer, str.charBuffer);
	}

	String String::SubString(unsigned pos) const
	{
		if (pos < length_)
		{
			String ret;
			ret.Resize(length_ - pos);
			CopyChars(ret.charBuffer, charBuffer + pos, ret.length_);

			return ret;
		}
		else
			return String();
	}

	String String::SubString(unsigned pos, unsigned length) const
	{
		if (pos < length_)
		{
			String ret;

			if (pos + length > length_)
				length = length_ - pos;

			ret.Resize(length);
			CopyChars(ret.charBuffer, charBuffer + pos, ret.length_);

			return ret;
		}
		else
			return String();
	}

	String String::Trimmed() const
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

		return SubString(start, end);
	}

	String String::ToUpper() const
	{
		String ret(*this);

		for (unsigned i = 0; i < ret.length_; i++)
			ret[i] = (char)toupper(ret[i]);

		return ret;
	}

	String String::ToLower() const
	{
		String ret(*this);

		for (unsigned i = 0; i < ret.length_; i++)
			ret[i] = (char)tolower(ret[i]);

		return ret;
	}

	std::vector<String> String::Split(char separator, bool keepEmptyStrings /*= false*/) const
	{
		return Split(CString(), separator, keepEmptyStrings);
	}

	void String::Join(const std::vector<String>& subStrings, const String& glue)
	{
		*this = Joined(subStrings, glue);
	}

	unsigned String::Find(char c, unsigned startInd /*= 0*/, bool caseSensetive /*= true*/) const
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
			c = (char)tolower(c);
			for (unsigned i = startInd; i < length_; ++i)
			{
				if (tolower(charBuffer[i]) == c)
					return i;
			}
		}

		return NOTFOUND;
	}

	unsigned String::Find(const String& str, unsigned startInd /*= 0*/, bool caseSensetive /*= true*/) const
	{
		if (!str.length_ || str.length_ > length_)
			return NOTFOUND;

		char first = str.charBuffer[0];
		if (!caseSensetive)
			first = (char)tolower(first);

		for (unsigned i = startInd; i < length_ - str.length_; ++i)
		{
			char c = charBuffer[i];
			if (!caseSensetive)
				c = (char)tolower(c);

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
						c = (char)tolower(c);
						d = (char)tolower(d);
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

	unsigned String::FindLast(char c, unsigned startInd, bool caseSensetive /*= true*/) const
	{
		if (startInd >= length_)
			startInd = length_ + 1;

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
			c = (char)tolower(c);
			for (unsigned i = startInd; i < length_; --i)
			{
				if (tolower(charBuffer[i]) == c)
					return i;
			}
		}

		return NOTFOUND;
	}

	unsigned String::FindLast(const String& str, unsigned startInd, bool caseSensetive /*= true*/) const
	{
		if (!str.length_ || str.length_ > length_)
			return NOTFOUND;
		if (startInd > length_ - str.length_)
			startInd = length_ - str.length_;

		char first = str.charBuffer[0];
		if (!caseSensetive)
			first = (char)tolower(first);

		for (unsigned i = startInd; i < length_ - str.length_; --i)
		{
			char c = charBuffer[i];
			if (!caseSensetive)
				c = (char)tolower(c);

			if (c == first)
			{
				bool found = true;

				for (unsigned j = 1; j < str.length_; ++j)
				{
					c = charBuffer[j + 1];
					char d = str.charBuffer[j];

					if (!caseSensetive)
					{
						c = (char)tolower(c);
						d = (char)tolower(d);
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

	bool String::StartsWith(const String& str, bool caseSensetive /*= true*/) const
	{
		return Find(str, 0, caseSensetive) == 0;
	}

	bool String::EndsWith(const String& str, bool caseSensetive /*= true*/) const
	{
		unsigned pos = FindLast(str, length_ - 1, caseSensetive);
		return pos != NOTFOUND && pos == length_ - str.length_;
	}

	int String::Compare(const String& str, bool caseSensetive /*= true*/) const
	{
		return Compare(CString(), str.CString(), caseSensetive);
	}

	int String::Compare(const char* str, bool caseSensetive /*= true*/) const
	{
		return Compare(CString(), str, caseSensetive);
	}

	bool String::Contains(const String& str, bool caseSensetive /*= true*/) const
	{
		return Find(str, 0, caseSensetive) != NOTFOUND;
	}

	bool String::Contains(char c, bool caseSensetive /*= true*/) const
	{
		return Find(c, 0, caseSensetive) != NOTFOUND;
	}

	void String::SetUTF8FromChar(const char* str)
	{
		char temp[7];

		Clear();

		if (!str)
			return;

		while (*str)
		{
			char* dest = temp;

			EncodeUTF8(dest, (unsigned)*str++);
			*dest = 0;
			Append(temp);
		}
	}

	void String::SetUTF8FromWChar(const wchar_t* str)
	{
		char temp[7];

		Clear();

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
			EncodeUTF8(dest, (unsigned)*str++);
			*dest = 0;
			Append(temp);
		}
#endif // WIN32
	}

	unsigned String::LengthUTF8() const
	{
		unsigned ret = 0;

		const char* src = charBuffer;
		if (!src)
			return ret;

		const char* end = charBuffer + length_;

		while (src < end)
		{
			DecodeUTF8(src);
			++ret;
		}

		return ret;
	}

	unsigned String::ByteOffsetUTF8(unsigned index) const
	{
		unsigned offset = 0;
		unsigned utfPos = 0;

		while (utfPos < index && offset < length_)
		{
			NextUTF8Char(offset);
			++utfPos;
		}

		return offset;
	}

	unsigned String::NextUTF8Char(unsigned& byteOffset) const
	{
		if (!charBuffer)
			return 0;

		const char* src = charBuffer + byteOffset;
		unsigned ret = DecodeUTF8(src);
		byteOffset = (unsigned)(src - charBuffer);

		return ret;
	}

	unsigned String::AtUTF8(unsigned index) const
	{
		unsigned byteOffset = ByteOffsetUTF8(index);
		return NextUTF8Char(byteOffset);
	}

	void String::ReplaceUTF8(unsigned index, unsigned uniChar)
	{
		unsigned utfPos = 0;
		unsigned offset = 0;

		while (utfPos < index && offset < length_)
		{
			NextUTF8Char(offset);
			++utfPos;
		}

		if (utfPos < index)
			return;

		unsigned begin = offset;
		NextUTF8Char(offset);

		char temp[7];
		char* dest = temp;
		EncodeUTF8(dest, uniChar);
		*dest = 0;

		Replace(begin, offset - begin, temp, (unsigned)(dest - temp));
	}

	String& String::AppendUTF8(unsigned uniChar)
	{
		char temp[7];
		char* dest = temp;
		EncodeUTF8(dest, uniChar);
		*dest = 0;

		return Append(temp);
	}

	String String::SubStringUTF8(unsigned pos) const
	{
		unsigned utfLength = LengthUTF8();
		unsigned offset = ByteOffsetUTF8(pos);
		String ret;

		while (pos < utfLength)
		{
			ret.AppendUTF8(NextUTF8Char(offset));
			++pos;
		}

		return ret;
	}

	String String::SubStringUTF8(unsigned pos, unsigned length) const
	{
		unsigned utfLength = LengthUTF8();
		unsigned offset = ByteOffsetUTF8(pos);
		unsigned end = pos + length;
		String ret;

		while (pos < end && pos < utfLength)
		{
			ret.AppendUTF8(NextUTF8Char(offset));
			++pos;
		}

		return ret;
	}

	unsigned String::ToHash() const
	{
		unsigned hash = 0;
		const char* ptr = charBuffer;
		while (ptr)
		{
			hash = *ptr + (hash << 6) + (hash << 16) - hash;
			++ptr;
		}

		return hash;
	}



	void String::MoveRange(unsigned dest, unsigned src, unsigned count)
	{
		if (count)
			memmove(charBuffer + dest, charBuffer + src, count);
	}

	void String::CopyChars(char* dest, const char* src, unsigned count)
	{
		char* end = dest + count;
		while (dest != end)
		{
			*dest = *src;
			++dest;
			++src;
		}
	}

	void String::Replace(unsigned pos, unsigned length, const char* src, unsigned srcLength)
	{
		int delta = (int)srcLength - (int)length;

		if (pos + length < length_)
		{
			if (delta < 0)
			{
				MoveRange(pos + srcLength, pos + length, length_ - pos - length);
				Resize(length_ + delta);
			}
			else if (delta > 0)
			{
				Resize(length_ + delta);
				MoveRange(pos + srcLength, pos + length, length_ - pos - length - delta);
			}
		}
		else
		{
			Resize(length_ + delta);
		}

		CopyChars(charBuffer + pos, src, srcLength);
	}



	std::vector<String> String::Split(const char* str, char separator, bool keepEmptyStrings /*= false*/)
	{
		std::vector<String> ret;
		const char* strEnd = str + String::CStringLength(str);

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

	std::vector<String> String::Split(const String& str, char separator, bool keepEmptyStrings /*= false*/)
	{
		return Split(str.CString(), separator, keepEmptyStrings);
	}

	String String::Joined(const std::vector<String>& subStrings, const String& glue)
	{
		if (subStrings.empty())
			return String();

		String joined(subStrings[0]);
		for (unsigned i = 1; i < subStrings.size(); ++i)
			joined.Append(glue).Append(subStrings[i]);

		return joined;
	}

	void String::EncodeUTF8(char*& dest, unsigned uniChar)
	{
		if (uniChar < 0x80)
			*dest++ = uniChar;
		else if (uniChar < 0x800)
		{
			dest[0] = (char)(0xc0 | (uniChar >> 6) & 0x1f);
			dest[1] = (char)(0x80 | uniChar & 0x3f);
			dest += 2;
		}
		else if (uniChar < 0x10000)
		{
			dest[0] = (char)(0xe0 | (uniChar >> 12) & 0xf);
			dest[1] = (char)(0x80 | (uniChar >> 6) & 0x3f);
			dest[2] = (char)(0x80 | uniChar & 0x3f);
			dest += 3;
		}
		else if (uniChar < 0x200000)
		{
			dest[0] = (char)(0xf0 | (uniChar >> 18) & 0x7);
			dest[1] = (char)(0x80 | (uniChar >> 12) & 0x3f);
			dest[2] = (char)(0x80 | (uniChar >> 6) & 0x3f);
			dest[3] = (char)(0x80 | uniChar & 0x3f);
			dest += 4;

		}
		else if (uniChar < 0x4000000)
		{
			dest[0] = (char)(0xf8 | (uniChar >> 24) & 0x3);
			dest[1] = (char)(0x80 | (uniChar >> 18) & 0x3f);
			dest[2] = (char)(0x80 | (uniChar >> 12) & 0x3f);
			dest[3] = (char)(0x80 | (uniChar >> 6) & 0x3f);
			dest[4] = (char)(0x80 | uniChar & 0x3f);
			dest += 5;
		}
		else
		{
			dest[0] = (char)(0xfc | (uniChar >> 30) & 0x1);
			dest[1] = (char)(0x80 | (uniChar >> 24) & 0x3f);
			dest[2] = (char)(0x80 | (uniChar >> 18) & 0x3f);
			dest[3] = (char)(0x80 | (uniChar >> 12) & 0x3f);
			dest[4] = (char)(0x80 | (uniChar >> 6) & 0x3f);
			dest[5] = (char)(0x80 | uniChar & 0x3f);
			dest += 6;
		}
	}

	unsigned String::DecodeUTF8(const char*& src)
	{
		if (src == nullptr)
			return 0;

		unsigned char char1 = *src++;

		if (char1 >= 0x80 && char1 < 0xc0)
		{
			while ((unsigned char)*src >= 0x80 && (unsigned char)*src < 0xc0)
				++src;
			return '?';
		}
		 //TODO: test this
		auto nextByte = [](const char*& src)
		{
			return ((((unsigned char)*src) < 0x80) || (((unsigned char)*src) >= 0xc0)) ? ('?') : *(++src);
		};
		
		if (char1 < 0x80)
			return char1;
		else if (char1 < 0xe0)
		{
			unsigned char char2 = nextByte(src);
			return (unsigned)((char2 & 0x3f) | ((char1 & 0x1f) << 6));
		}
		else if (char1 < 0xf0)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			return (unsigned)((char3 & 0x3f) | ((char2 & 0x3f) << 6) | ((char1 & 0xf) << 12));
		}
		else if (char1 < 0xf8)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			return (unsigned)((char4 & 0x3f) | ((char3 & 0x3f) << 6) | ((char2 & 0x3f) << 12) | ((char1 & 0x7) << 18));
		}
		else if (char1 < 0xfc)
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			unsigned char char5 = nextByte(src);
			return (unsigned)((char5 & 0x3f) | ((char4 & 0x3f) << 6) | ((char3 & 0x3f) << 12) | ((char2 & 0x3f) << 18) | ((char1 & 0x3) << 24));
		}
		else
		{
			unsigned char char2 = nextByte(src);
			unsigned char char3 = nextByte(src);
			unsigned char char4 = nextByte(src);
			unsigned char char5 = nextByte(src);
			unsigned char char6 = nextByte(src);
			return (unsigned)((char6 & 0x3f) | ((char5 & 0x3f) << 6) | ((char4 & 0x3f) << 12) | ((char3 & 0x3f) << 18) | ((char2 & 0x3f) << 24) | ((char1 & 0x1) << 30));
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

	unsigned String::CStringLength(const char* str)
	{
		return str ? (unsigned)strlen(str) : 0;
	}

	int String::Compare(const char* str1, const char* str2, bool caseSensetive /*= true*/)
	{
		if (!str1 || !str2)
			return str1 ? 1 : (str2 ? -1 : 0);

		if (caseSensetive)
			return strcmp(str1, str2);
		else
		{
			while(true)
			{
				char l = (char)tolower(*str1);
				char r = (char)tolower(*str2);
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

	int String::Compare(const String& str1, const String& str2, bool caseSensetive /*= true*/)
	{
		return Compare(str1.CString(), str2.CString(), caseSensetive);
	}

	WString::WString()
		: length_(0), wñharBuffer(nullptr)
	{}

	WString::WString(const String& str)
		: length_(0), wñharBuffer(nullptr)
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
		wchar_t* dest = wñharBuffer;
		while (offset < str.Length())
			String::EncodeUTF16(dest, str.NextUTF8Char(offset));
#else
		Resize(str.LengthUTF8());

		unsigned offset = 0;
		wchar_t* dest = wñharBuffer;
		while (offset < str.Length())
			*dest++ = (wchar_t)str.NextUTF8Char(offset);
#endif
	}

	WString::~WString()
	{
		delete[] wñharBuffer;
	}

	wchar_t& WString::operator[](unsigned index)
	{
		assert(index < length_);
		return wñharBuffer[index];
	}

	const wchar_t& WString::operator[](unsigned index) const
	{
		assert(index < length_);
		return wñharBuffer[index];
	}

	wchar_t& WString::At(unsigned index)
	{
		assert(index < length_);
		return wñharBuffer[index];
	}

	const wchar_t& WString::At(unsigned index) const
	{
		assert(index < length_);
		return wñharBuffer[index];
	}

	void WString::Resize(unsigned newLength)
	{
		if (!newLength)
		{
			delete[] wñharBuffer;
			wñharBuffer = nullptr;
			length_ = 0;
		}
		else
		{
			wchar_t* newBuffer = new wchar_t[newLength + 1];
			if (wñharBuffer)
			{
				unsigned copyLength = length_ < newLength ? length_ : newLength;
				memcpy(newBuffer, wñharBuffer, copyLength * sizeof(wchar_t));
				delete[] wñharBuffer;
			}

			newBuffer[newLength] = 0;
			wñharBuffer = newBuffer;
			length_ = newLength;
		}
	}
}
