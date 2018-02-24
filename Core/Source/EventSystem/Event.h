#pragma once
#include <vector>
#include "Delegate.h"

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
		template<typename R(*Function)(Args...)>
		void Add()
		{
			Add(Delegate<R(Args...)>::Create<Function>());
		}

		template<typename R(*Function)(Args...)>
		void Remove()
		{
			Remove(Delegate<R(Args...)>::Create<Function>());
		}
		template<class C, typename R(C::*Function)(Args...)>
		void Add(C* instance)
		{
			Add(Delegate<R(Args...)>::Create<C, Function>(instance));
		}

		template<class C, typename R(*Function)(Args...)>
		void Remove(C* instance)
		{
			Remove(Delegate<R(Args...)>::Create<C, Function>(instance));
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
				delegate.Invoke(args...);
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

