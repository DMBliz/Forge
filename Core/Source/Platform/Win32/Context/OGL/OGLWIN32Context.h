#pragma once
#include "Platform/Api/Context.h"
#include "windows.h"
#include "Types.h"

namespace Forge
{

	class OGLWIN32Context : public Context
	{
	private:
		HWND window;
		HDC deviceContext = 0;
		HGLRC renderContext = 0;
		ATOM windowClass;
		
	public:
		OGLWIN32Context();
		~OGLWIN32Context();

		void CreateContext(const Window& win, unsigned int sampleCount) override;
		void CreateContext(unsigned sampleCount) override;
		void DeleteContext() override;
		void SendMsg(const int* hwnd, int msg, const int wParam, const int lParam) override;
		void PlatformUpdate() override;
	};

}
