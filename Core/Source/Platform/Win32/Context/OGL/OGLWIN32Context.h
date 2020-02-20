#pragma once
#include "Platform/Api/Context.h"
#include "windows.h"
#include "Types.h"

namespace Forge
{

	class OGLWin32Context : public Context
	{
	private:
		HWND window;
		HDC deviceContext = 0;
		HGLRC renderContext = 0;
		ATOM windowClass;
		
		/**
			creates temp context, loads wgl functions and deletes temp context, 
			because in windows to create normal context you should create context
			@return true if glad loaded, false if somthing fails
		*/
		bool loadGladWithTempWindow();
	public:
        OGLWin32Context();
		~OGLWin32Context();
		void CreateContext(Window& win, unsigned int sampleCount) override;
		void DeleteContext() override;
		void PlatformUpdate() override;
		void setActive() override;
	};

}
