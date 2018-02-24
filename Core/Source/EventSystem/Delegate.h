#pragma once
#include <utility>

namespace Forge
{
	template<typename T>
	class Delegate;

	template<typename R,typename ...Args>
	class Delegate<R(Args...)>
	{
		using InstancePtr = void*;
		using InternalFunction = R(*)(InstancePtr, Args...);
		using Stub = std::pair<InstancePtr, InternalFunction>;

		template<R(*Function)(Args...)>
		static R FunctionStub(InstancePtr,Args... args)
		{
			return (Function)(args...);
		}

		template<class C, R(C::*Function)(Args...)>
		static R ClassMethodStub(InstancePtr instance, Args... args)
		{
			return (static_cast<C*>(instance)->*Function)(args...);
		}

	private:
		Stub stub;
		Delegate(void* instance, InternalFunction callbackFunction)
			:stub{ instance, callbackFunction }
		{}
	public:
		Delegate()
			:stub(nullptr, nullptr)
		{}

		R operator()(Args... args)
		{
			return stub.second(stub.first, args...);
		}

		bool operator==(const Delegate& other)
		{
			return stub.first == other.stub.first && stub.second == other.stub.second;
		}

		template<R(*Function)(Args...)>
		void Bind()
		{
			stub.first = nullptr;
			stub.second = &FunctionStub<Function>;
		}

		template<class C, R(C::*Function)(Args...)>
		void Bind(C* instance)
		{
			stub.first = instance;
			stub.second = &ClassMethodStub<C, Function>;
		}

		R Invoke(Args... args)
		{
			return stub.second(stub.first, args...);
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
