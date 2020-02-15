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

		void MoveRange(unsigned dest, unsigned src, unsigned count);
		void Replace(unsigned pos, unsigned length, const char* src, unsigned srcLength);
		static void CopyChars(char* dest, const char* src, unsigned count);

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

		char& At(unsigned index);
		const char& At(unsigned index) const;

		void Replace(char oldChar, char newChar, bool caseSensetive = true);
		void Replace(const String& oldValue, const String& newValue, bool caseSensetive = true);
		void Replace(unsigned pos, unsigned length, const String& newValue);
		void Replace(unsigned pos, unsigned length, const char* newValue);
		String Replaced(char oldChar, char newChar, bool caseSensetive = true);
		String Replaced(const String& oldValue, const String& newValue, bool caseSensetive = true);

		String& Append(const String& str);
		String& Append(const char* str);
		String& Append(char c);
		String& Append(const char* str, unsigned length);

		void Insert(unsigned pos, const String& str);
		void Insert(unsigned pos, char c);

		void Erase(unsigned pos, unsigned length = 1);

		void Resize(unsigned newLength);
		void Reserve(unsigned newCapacity);
		void Compact();
		void Clear();
		void Swap(String& str);

		char First() const { return charBuffer[0]; }
		char Last() const { return length_ ? charBuffer[length_ - 1] : charBuffer[0]; }

		String SubString(unsigned pos) const;
		String SubString(unsigned pos, unsigned length) const;
		String Trimmed() const;
		String ToUpper() const;
		String ToLower() const;

		std::vector<String> Split(char separator, bool keepEmptyStrings = false) const;
		void Join(const std::vector<String>& subStrings, const String& glue);
		
		unsigned Find(const String& str, unsigned startInd = 0, bool caseSensetive = true) const;
		unsigned Find(char c, unsigned startInd = 0, bool caseSensetive = true) const;
		unsigned FindLast(const String& str, unsigned startInd, bool caseSensetive = true) const;
		unsigned FindLast(char c, unsigned startInd, bool caseSensetive = true) const;

		bool StartsWith(const String& str, bool caseSensetive = true) const;
		bool EndsWith(const String& str, bool caseSensetive = true) const;

		int Compare(const String& str, bool caseSensetive = true) const;
		int Compare(const char* str, bool caseSensetive = true) const;

		bool Contains(const String& str, bool caseSensetive = true) const;
		bool Contains(char c, bool caseSensetive = true) const;
		
		bool IsEmpty() const { return length_ == 0; }

		const char* CString() const { return charBuffer; }
		char* CString() { return charBuffer; }
		unsigned Length() const { return length_; }
		unsigned Capacity() const { return capacity_; }


		void SetUTF8FromChar(const char* str);
		void SetUTF8FromWChar(const wchar_t* str);
		unsigned LengthUTF8() const;
		unsigned ByteOffsetUTF8(unsigned index) const;
		unsigned NextUTF8Char(unsigned& byteOffset) const;
		unsigned AtUTF8(unsigned index) const;
		void ReplaceUTF8(unsigned index, unsigned uniChar);
		String& AppendUTF8(unsigned uniChar);
		String SubStringUTF8(unsigned pos) const;
		String SubStringUTF8(unsigned pos, unsigned length) const;

		unsigned ToHash() const;


		friend std::ostream& operator<<(std::ostream& os, const String& obj)
		{
			return os << obj.charBuffer;
		}

		static const String Empty;

		static std::vector<String> Split(const char* str, char separator, bool keepEmptyStrings = false);
		static std::vector<String> Split(const String& str, char separator, bool keepEmptyStrings = false);
		static String Joined(const std::vector<String>& subStrings, const String& glue);

		static void EncodeUTF8(char*& dest, unsigned uniChar);
		static unsigned DecodeUTF8(const char*& src);

#ifdef _WIN32
		static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
		static unsigned DecodeUTF16(const wchar_t*& src);
#endif

		static unsigned CStringLength(const char* str);

		static int Compare(const char* str1, const char* str2, bool caseSensetive = true);
		static int Compare(const String& str1, const String& str2, bool caseSensetive = true);
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

		wchar_t& At(unsigned index);
		const wchar_t& At(unsigned index) const;

		void Resize(unsigned newLength);

		bool Empty() const { return length_ == 0; };

		unsigned Length() const { return length_; }

		const wchar_t* CString() const { return wcharBuffer; }

	};

}
