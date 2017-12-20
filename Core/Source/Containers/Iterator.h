#pragma once

namespace Forge
{
	template<class T>
	class Iterator
	{
		T* pointer;
	public:
		Iterator()
			: pointer(0)
		{}

		explicit Iterator(T* ptr)
			: pointer(ptr)
		{}

		T* operator ->() const { return pointer; }
		T* operator *() const { return pointer; }

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
			ptr += value;
			return *this;
		}

		Iterator<T> operator-=(int value)
		{
			ptr -= value;
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

		int operator -(const Iterator& rhs) const { return (int)(pointer - rhs.pointer); }

		bool operator ==(const Iterator& rhs) const { return pointer == rhs.pointer; }

		bool operator !=(const Iterator& rhs) const { return pointer != rhs.pointer; }

		bool operator <(const Iterator& rhs) const { return pointer < rhs.pointer; }

		bool operator >(const Iterator& rhs) const { return pointer > rhs.pointer; }

		bool operator <=(const Iterator& rhs) const { return pointer <= rhs.pointer; }

		bool operator >=(const Iterator& rhs) const { return pointer >= rhs.pointer; }
	};

}
