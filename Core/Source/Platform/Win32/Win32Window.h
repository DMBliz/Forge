#pragma once
#include "Platform/Api/Window.h"
#include "Windows.h"
#include "Win32Input.h"

namespace Forge
{
	class Win32Window : public Window
	{
		friend class Win32Input;
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

		Win32Input winInput;

		HDC deviceContext;
		HGLRC renderContext;
		
		void ProcessResize(const Vector2i& size);
		void ProcessMove();
		static LRESULT CALLBACK WindProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    public:
        Win32Window();
        ~Win32Window();

        void create(const WindowCreationDesc &creationDesc) override;
        void close() override;
        void show() override;
        void hide() override;

        void setClipboard(const String &data) override;
        const String &getClipboard() override;

		void setWindowRect(const RectI& newSize) override;
		void setTitle(const String& newTitle) override;

        void setWindowState(WindowState windowState) override;

        HWND GetNativeWindow() const { return _hwnd; }

		HMONITOR GetMonitor() const { return _monitor; }

		void platformUpdate() override;

        Win32Input* getInput() override;

    protected:
		void setCursorPosition(const Vector2i& newPos) override;
	};

}
