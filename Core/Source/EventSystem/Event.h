#pragma once
#include <vector>
#include "Delegate.h"
#include "Defines.h"

namespace Forge
{
	template<typename T>
	class Event;

	template<typename R, typename ...Args>
	class Event<R(Args...)>
	{
	private:
		std::vector<Delegate<R(Args...)>> delegates;
	public:


		template<R(*Function)(Args...)>
		void Add()
		{
			Add(Delegate<R(Args...)>::template create<Function>());
		}

		template<R(*Function)(Args...)>
		void Remove()
		{
			Remove(Delegate<R(Args...)>::template create<Function>());
		}

		template<class C,  R(C::*Function)(Args...)>
		void Add(C* instance)
		{
			Add(Delegate<R(Args...)>::template create<C, Function>(instance));
		}

		template<class C, R(C::*Function)(Args...)>
		void Remove(C* instance)
		{
			Remove(Delegate<R(Args...)>::template create<C, Function>(instance));
		}

		void Add(Delegate<R(Args...)> delegate)
		{
			delegates.push_back(delegate);
		}

		void Remove(Delegate<R(Args...)> delegate)
		{
			auto it = std::find(delegates.begin(), delegates.end(), delegate);
			if(it != delegates.end())
			{
				delegates.erase(it);
			}
		}

		void operator()(Args... args)
		{
			for (auto& delegate : delegates)
			{
				delegate(args...);
			}
		}

		void Invoke(Args... args)
		{
			for (auto& delegate : delegates)
			{
				delegate.Invoke(args...);
			}
			
		}
	};
}

