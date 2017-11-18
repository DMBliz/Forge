#pragma once

namespace Forge
{
	template <class T>
	void Swap(T& first, T& second)
	{
		T temp = first;
		first = second;
		second = temp;
	}
}