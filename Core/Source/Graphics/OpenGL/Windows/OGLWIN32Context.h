#pragma once
#include "Graphics/Context.h"
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

		void CreateContext(const Window& win, unsigned int sampleCount, bool debugRenderer) override;
		void CreateContext(unsigned sampleCount, bool debugRenderer) override;
		void DeleteContext() override;
		void SendMsg(const int* hwnd, int msg, const int wParam, const int lParam) override;
		void PlatformUpdate() override;
	};

}
