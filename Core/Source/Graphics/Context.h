#pragma once

namespace Forge
{
	class Window;

	class Context
	{
	public:
		virtual void CreateContext(const Window& win, unsigned int sampleCount, bool debugRenderer) = 0;
		virtual void CreateContext( unsigned int sampleCount, bool debugRenderer) = 0;
		virtual void DeleteContext() = 0;
		virtual void SendMsg(const int* hwnd, int msg, const int wParam, const int lParam) = 0;
		virtual void PlatformUpdate() = 0;

		static Context* Create();
	};

}
