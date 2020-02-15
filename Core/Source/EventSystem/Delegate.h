#pragma once
#include <utility>

namespace Forge
{
	template<typename T>
	class Delegate;

	template<typename R,typename ...Args>
	class Delegate<R(Args...)>
	{
		using InternalFunction = R(*)(void*, Args...);

		template<R(*Function)(Args...)>
		static R FunctionStub(void*,Args... args)
		{
			return (Function)(args...);
		}

		template<class C, R(C::*Function)(Args...)>
		static R ClassMethodStub(void* instance, Args... args)
		{
			return (static_cast<C*>(instance)->*Function)(args...);
		}

	private:
        InternalFunction callback{ nullptr };
		void* callee{ nullptr };

		Delegate(void* instance, InternalFunction callbackFunction)
			:callee{ instance }, callback{ callbackFunction}
		{}
	public:
		Delegate()
		{}

		R operator()(Args... args)
		{
		    return callback(callee, args...);
		}

		bool operator==(const Delegate& other)
		{
			return callee == other.callee && callback == other.callback;
		}

		template<R(*Function)(Args...)>
		void Bind()
		{
			callee = nullptr;
			callback = &FunctionStub<Function>;
		}

		template<class C, R(C::*Function)(Args...)>
		void Bind(C* instance)
		{
			callee = instance;
			callback = &ClassMethodStub<C, Function>;
		}

		R Invoke(Args... args)
		{
            return callback(callee, args...);
		}

		template<R(*Function)(Args...)>
		static Delegate Create()
		{
			return Delegate{ nullptr, &FunctionStub<Function> };
		}

		template<class C, R(C::*Function)(Args...)>
		static Delegate Create(C* instance)
		{
			return Delegate{ instance, &ClassMethodStub<C, Function> };
		}

	};
}
