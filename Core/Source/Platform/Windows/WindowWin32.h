#pragma once
#include "Platform/Window.h"
#include "windows.h"
#include "Defines.h"

namespace Forge
{

	class WindowWin32 : public Window
	{
	private:
		HWND _hwnd = nullptr;
		HMONITOR _monitor = nullptr;
		ATOM _windowClass = 0;
		DWORD _windowStyle = 0;
		DWORD _windowExStyle = 0;
		DWORD _windowWindowedStyle = 0;
		DWORD _wdindowFullScreenStyle = 0;
		Vector2i windowedSize;
		Vector2i windowedPos;

		void ProcessResize(const Vector2i& size);
		void ProcessMove();
		static LRESULT CALLBACK WindProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	public:

		WindowWin32();
		~WindowWin32();

		void Create(const Vector2i& size, const String& title, bool Resizable, bool FullScreen, bool ExclusiveFullScreen, bool HighDPI, bool depth) override;

		void SetSize(const Vector2i& newSize) override;

		void SetTitle(const String& newTitle) override;

		void SetFullScreen(bool value) override;

		void Close() override;

		HWND GetNativeWindow() const { return _hwnd; }

		HMONITOR GetMonitor() const { return _monitor; }

	};

}
