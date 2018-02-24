#pragma once

namespace Forge
{
	template<class T>
	class Iterator
	{
		T* pointer;
	public:
		Iterator()
			: pointer(nullptr)
		{}

		explicit Iterator(T* ptr)
			: pointer(ptr)
		{}

		T* operator ->() const { return pointer; }
		T& operator *() const { return *pointer; }

		Iterator<T> operator++()
		{
			++pointer;
			return *this;
		}

		Iterator<T> operator++(int)
		{
			Iterator<T> it = *this;
			++pointer;
			return it;
		}

		Iterator<T> operator--()
		{
			--pointer;
			return *this;
		}

		Iterator<T> operator--(int)
		{
			Iterator<T> it = *this;
			--pointer;
			return it;
		}

		Iterator<T> operator+=(int value)
		{
			pointer += value;
			return *this;
		}

		Iterator<T> operator-=(int value)
		{
			pointer -= value;
			return *this;
		}

		Iterator<T> operator+(int value)
		{
			return Iterator<T>(pointer + value);
		}

		Iterator<T> operator-(int value)
		{
			return Iterator<T>(pointer - value);
		}

		int operator -(const Iterator& rhs) const { return static_cast<int>(pointer - rhs.pointer); }

		bool operator ==(const Iterator& rhs) const { return pointer == rhs.pointer; }

		bool operator !=(const Iterator& rhs) const { return pointer != rhs.pointer; }

		bool operator <(const Iterator& rhs) const { return pointer < rhs.pointer; }

		bool operator >(const Iterator& rhs) const { return pointer > rhs.pointer; }

		bool operator <=(const Iterator& rhs) const { return pointer <= rhs.pointer; }

		bool operator >=(const Iterator& rhs) const { return pointer >= rhs.pointer; }
	}; 
	
	template<class T>
	class ConstIterator
	{
		T* pointer;
	public:
		ConstIterator()
			: pointer(nullptr)
		{}

		explicit ConstIterator(T* ptr)
			: pointer(ptr)
		{}

		explicit ConstIterator(const Iterator<T>& ptr)
			: pointer(ptr)
		{}

		ConstIterator<T>& operator=(const Iterator<T>& rhs)
		{
			pointer = rhs.pointer;
			return *this;
		}

		const T* operator ->() const { return pointer; }
		const T& operator *() const { return *pointer; }

		ConstIterator<T> operator++()
		{
			++pointer;
			return *this;
		}

		ConstIterator<T> operator++(int)
		{
			ConstIterator<T> it = *this;
			++pointer;
			return it;
		}

		ConstIterator<T> operator--()
		{
			--pointer;
			return *this;
		}

		ConstIterator<T> operator--(int)
		{
			ConstIterator<T> it = *this;
			--pointer;
			return it;
		}

		ConstIterator<T> operator+=(int value)
		{
			pointer += value;
			return *this;
		}

		ConstIterator<T> operator-=(int value)
		{
			pointer -= value;
			return *this;
		}

		ConstIterator<T> operator+(int value)
		{
			return ConstIterator<T>(pointer + value);
		}

		ConstIterator<T> operator-(int value)
		{
			return ConstIterator<T>(pointer - value);
		}

		int operator -(const ConstIterator& rhs) const { return static_cast<uint>(pointer - rhs.pointer); }

		bool operator ==(const ConstIterator& rhs) const { return pointer == rhs.pointer; }

		bool operator !=(const ConstIterator& rhs) const { return pointer != rhs.pointer; }

		bool operator <(const ConstIterator& rhs) const { return pointer < rhs.pointer; }

		bool operator >(const ConstIterator& rhs) const { return pointer > rhs.pointer; }

		bool operator <=(const ConstIterator& rhs) const { return pointer <= rhs.pointer; }

		bool operator >=(const ConstIterator& rhs) const { return pointer >= rhs.pointer; }
	};

}
