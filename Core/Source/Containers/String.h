#pragma once

#include <vector>
#include <cstdarg>
#include <cctype>
#include <ostream>

namespace Forge
{
	class WString;

	class String
	{
	public:
		static const int CONVERSION_BUFFER_LENGTH = 128;
		static const unsigned NOTFOUND = 0xffffffff;
		static const unsigned MIN_CAPACITY = 8;

	private:
		char* charBuffer;
		unsigned length_;
		unsigned capacity_;

		void moveRange(unsigned dest, unsigned src, unsigned count);
		void replace(unsigned pos, unsigned length, const char* src, unsigned srcLength);
		static void copyChars(char* dest, const char* src, unsigned count);

	public:
		String();
		String(const String& str);
		String(const char* str);
		String(char* str);
		String(const char* str, unsigned length);
		String(const wchar_t* str);
		String(wchar_t* str);
		String(const WString& str);

		explicit String(int value);
		explicit String(short value);
		explicit String(long value);
		explicit String(long long value);
		explicit String(unsigned value);
		explicit String(unsigned short value);
		explicit String(unsigned long value);
		explicit String(unsigned long long value);
		explicit String(float value);
		explicit String(double value);
		explicit String(bool value);
		explicit String(char value);
		explicit String(char value, int length);

		~String();


		String& operator=(const String& rhs);
		String& operator=(const char* rhs);

		String& operator+=(const String& rhs);
		String& operator+=(const char* rhs);
		String& operator+=(char rhs);

		String& operator+=(int value);
		String& operator+=(short value);
		String& operator+=(long value);
		String& operator+=(long long value);
		String& operator+=(unsigned value);
		String& operator+=(unsigned short value);
		String& operator+=(unsigned long value);
		String& operator+=(unsigned long long value);
		String& operator+=(float value);
		String& operator+=(double value);
		String& operator+=(bool value);

		template<class T>
		String operator+=(const T& rhs);

		String operator+(const String& rhs) const;
		String operator+(const char* rhs) const;
		friend String operator+(const char* lhs, const String& rhs);
		friend String operator+(const wchar_t* lhs, const String& rhs);

		bool operator==(const String& rhs) const;
		bool operator!=(const String& rhs) const;
		bool operator>(const String& rhs) const;
		bool operator<(const String& rhs) const;

		bool operator==(const char* rhs) const;
		bool operator!=(const char* rhs) const;
		bool operator>(const char* rhs) const;
		bool operator<(const char* rhs) const;

		char& operator[](unsigned index);
		const char& operator[](unsigned index) const;

		char& at(unsigned index);
		const char& at(unsigned index) const;

		void replace(char oldChar, char newChar, bool caseSensetive = true);
		void replace(const String& oldValue, const String& newValue, bool caseSensetive = true);
		void replace(unsigned pos, unsigned length, const String& newValue);
		void replace(unsigned pos, unsigned length, const char* newValue);
		String replaced(char oldChar, char newChar, bool caseSensetive = true);
		String replaced(const String& oldValue, const String& newValue, bool caseSensetive = true);

		String& append(const String& str);
		String& append(const char* str);
		String& append(char c);
		String& append(const char* str, unsigned length);

		void insert(unsigned pos, const String& str);
		void insert(unsigned pos, char c);

		void erase(unsigned pos, unsigned length = 1);

		void resize(unsigned newLength);
		void reserve(unsigned newCapacity);
		void compact();
		void clear();
		void swap(String& str);

		char first() const { return charBuffer[0]; }
		char last() const { return length_ ? charBuffer[length_ - 1] : charBuffer[0]; }

		String subString(unsigned pos) const;
		String subString(unsigned pos, unsigned length) const;
		String trimmed() const;
		String toUpper() const;
		String toLower() const;

		std::vector<String> split(char separator, bool keepEmptyStrings = false) const;
		void join(const std::vector<String>& subStrings, const String& glue);
		
		unsigned find(const String& str, unsigned startInd = 0, bool caseSensetive = true) const;
		unsigned find(char c, unsigned startInd = 0, bool caseSensetive = true) const;
		unsigned findLast(const String& str, unsigned startInd, bool caseSensetive = true) const;
		unsigned findLast(char c, unsigned startInd, bool caseSensetive = true) const;

		bool startsWith(const String& str, bool caseSensetive = true) const;
		bool endsWith(const String& str, bool caseSensetive = true) const;

		int compare(const String& str, bool caseSensetive = true) const;
		int compare(const char* str, bool caseSensetive = true) const;

		bool contains(const String& str, bool caseSensetive = true) const;
		bool contains(char c, bool caseSensetive = true) const;
		
		bool isEmpty() const { return length_ == 0; }

		const char* cString() const { return charBuffer; }
		char* cString() { return charBuffer; }
		unsigned length() const { return length_; }
		unsigned capacity() const { return capacity_; }


		void setUTF8FromChar(const char* str);
		void setUTF8FromWChar(const wchar_t* str);
		unsigned lengthUTF8() const;
		unsigned byteOffsetUTF8(unsigned index) const;
		unsigned nextUTF8Char(unsigned& byteOffset) const;
		unsigned atUTF8(unsigned index) const;
		void replaceUTF8(unsigned index, unsigned uniChar);
		String& appendUTF8(unsigned uniChar);
		String subStringUTF8(unsigned pos) const;
		String subStringUTF8(unsigned pos, unsigned length) const;

		unsigned hash() const;


		friend std::ostream& operator<<(std::ostream& os, const String& obj)
		{
			return os << obj.charBuffer;
		}

		static const String Empty;

		static std::vector<String> split(const char* str, char separator, bool keepEmptyStrings = false);
		static std::vector<String> split(const String& str, char separator, bool keepEmptyStrings = false);
		static String joined(const std::vector<String>& subStrings, const String& glue);

		static void encodeUTF8(char*& dest, unsigned uniChar);
		static unsigned decodeUTF8(const char*& src);

#ifdef _WIN32
		static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
		static unsigned DecodeUTF16(const wchar_t*& src);
#endif

		static unsigned cStringLength(const char* str);

		static int compare(const char* str1, const char* str2, bool caseSensetive = true);
		static int compare(const String& str1, const String& str2, bool caseSensetive = true);
	};


	class WString
	{
	private:
		wchar_t* wcharBuffer;
		unsigned length_;
	public:
		WString();
		WString(const String& str);
		~WString();

		wchar_t& operator[](unsigned index);
		const wchar_t& operator[](unsigned index) const;

		wchar_t& at(unsigned index);
		const wchar_t& at(unsigned index) const;

		void resize(unsigned newLength);

		bool empty() const { return length_ == 0; };

		unsigned length() const { return length_; }

		const wchar_t* cString() const { return wcharBuffer; }

	};

}
