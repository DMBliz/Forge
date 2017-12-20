#include "WindowWin32.h"
#include "Containers/String.h"
#include "Math/Vector2.h"
#include <Windowsx.h>
#include "Defines.h"


namespace Forge
{
	const wchar_t* classname = L"ForgeWindow";
	

	WindowWin32::WindowWin32()
	{
	}

	WindowWin32::~WindowWin32()
	{
		//TOD
	}

	void WindowWin32::Create(const Vector2i& size, const String& title, bool Resizable, bool FullScreen, bool ExclusiveFullScreen, bool HighDPI, bool depth)
	{
		this->windowSize = size;
		this->windowTitle = title;
		this->resizable = Resizable;
		this->fullScreen = FullScreen;
		this->exclusiveFullScreen = ExclusiveFullScreen;
		this->highDPI = HighDPI;

		if (highDPI)
		{
			HMODULE shcore = LoadLibraryW(L"shcore.dll");

			if (shcore)
			{
				typedef HRESULT(STDAPICALLTYPE *SetProcessDPIAwarenessProc)(int value);
				SetProcessDPIAwarenessProc setProcessDpiAwareness = reinterpret_cast<SetProcessDPIAwarenessProc>(GetProcAddress(shcore, "SetProcessDpiAwareness"));

				if (setProcessDpiAwareness)
					setProcessDpiAwareness(2);
			}
		}

		HINSTANCE instance = GetModuleHandleW(nullptr);

		WNDCLASSEXW wc;
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = &WindProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = instance;
		wc.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(101));
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = classname;
		wc.hIconSm = nullptr;

		_windowClass = RegisterClassExW(&wc);
		if (!_windowClass)
		{
			//TODO log fatal error
			LOG("can't register window class");
			return;
		}

		_windowWindowedStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_GROUP | WS_TABSTOP;

		if (Resizable)
			_windowWindowedStyle |= WS_SIZEBOX | WS_MAXIMIZEBOX;

		_wdindowFullScreenStyle = WS_CLIPSIBLINGS | WS_GROUP | WS_TABSTOP;

		int x = CW_USEDEFAULT;
		int y = CW_USEDEFAULT;

		_windowStyle = _windowWindowedStyle;
		_windowExStyle = WS_EX_APPWINDOW;

		RECT windowRect = { 0, 0, static_cast<LONG>(size.x), static_cast<LONG>(size.y) };
		AdjustWindowRectEx(&windowRect, _windowStyle, FALSE, _windowExStyle);

		int width = CW_USEDEFAULT;
		int height = CW_USEDEFAULT;

		if (size.x > 0.0f) width = windowRect.right - windowRect.left;
		if (size.y > 0.0f) height = windowRect.bottom - windowRect.top;


		wchar_t titleBuff[256] = L"game";
		if (!title.IsEmpty())
		{
			WString tmp(title);
			wcsncpy_s(titleBuff, tmp.CString(), tmp.Length());
		}

		_hwnd = CreateWindowExW(_windowExStyle, classname, titleBuff, _windowStyle, 
								x, y, width, height, nullptr, nullptr, instance, nullptr);

		if (!_hwnd)
		{
			//TODO fatal error 
			LOG("can't create window");
			return;
		}

		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);

		if (fullScreen)
			SetFullScreen(fullScreen);

		GetClientRect(_hwnd, &windowRect);

		windowSize.x = width;
		windowSize.y = height;
		windowResolution = windowSize;

		if (!RegisterTouchWindow(_hwnd, SW_SHOW))
		{
			//TOOD warning
			LOG("cant register touch window");
		}
		ShowWindow(_hwnd, SW_SHOW);
		SetWindowLongPtr(_hwnd, GWL_USERDATA, (LONG_PTR)this);

	}

	void WindowWin32::SetSize(const Vector2i& newSize)
	{
		Window::SetSize(newSize);

		RECT rect = { 0, 0, static_cast<LONG>(newSize.x), static_cast<LONG>(newSize.y) };
		AdjustWindowRectEx(&rect, _windowStyle, GetMenu(_hwnd) ? TRUE : FALSE, _windowExStyle);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		SetWindowPos(_hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

		windowResolution = windowSize;

		if (listener)
		{
			listener->onResolutionChange(windowResolution);
		}
	}

	void WindowWin32::SetTitle(const String& newTitle)
	{
		if(windowTitle == newTitle)
			return;

		SetWindowTextW(_hwnd, WString(windowTitle).CString());
		Window::SetTitle(newTitle);
	}

	void WindowWin32::SetFullScreen(bool value)
	{
		Window::SetFullScreen(value);

		if (exclusiveFullScreen)
		{
			//TODO: renderer set fullscreen
		}
		else
		{
			_windowStyle = (value ? _wdindowFullScreenStyle : _windowWindowedStyle);
			SetWindowLong(_hwnd, GWL_STYLE, _windowStyle);

			if (value)
			{
				RECT rect;
				GetWindowRect(_hwnd, &rect);

				windowedPos.Set(static_cast<int>(rect.left), static_cast<int>(rect.top));
				windowedSize.Set(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));
				
				windowResolution = windowSize;

				std::unique_lock<std::mutex> lock(listenerMutex);
				if (listener)
				{
					listener->onResolutionChange(windowResolution);
				}
			}
		}
	}

	void WindowWin32::Close()
	{
		SendMessage(_hwnd, WM_CLOSE, 0, 0);
	}

	void WindowWin32::ProcessResize(const Vector2i& size)
	{
		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);

		windowSize = size;
		windowResolution = size;

		std::unique_lock<std::mutex> lock(listenerMutex);
		if (listener)
		{
			listener->onSizeChange(windowSize);
			listener->onSizeChange(windowResolution);
		}
	}

	void WindowWin32::ProcessMove()
	{
		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);
	}

	LRESULT CALLBACK WindowWin32::WindProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{

		WindowWin32* win = reinterpret_cast<Forge::WindowWin32*>(GetWindowLongPtr(handle, GWLP_USERDATA));

		if (!win)
			return DefWindowProcW(handle, message, wParam, lParam);

		switch (message)
		{
			case WM_ACTIVATEAPP:
			{
				if (wParam)
				{
					//TODO: resume engine work
				}
				else
				{
					//TODO: pause engine work
				}
				break;
			}
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				UINT key = static_cast<UINT>(wParam);
				switch (key)
				{
					case VK_MENU:
						if ((lParam & 0x1000000) == 0)
							key = VK_LMENU;
						else
							key = VK_RMENU;
						break;
					case VK_CONTROL:
						if ((lParam & 0x1000000) == 0)
							key = VK_LCONTROL;
						else
							key = VK_RCONTROL;
						break;
					case VK_SHIFT:
						key = MapVirtualKey((lParam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
						break;
					default:
						break;
				}

				if (message == WM_KEYDOWN)
				{
					//TODO: input key down
				}
				else if (message == WM_KEYUP)
				{
					//TODO: input key up
				}
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			{
				LONG_PTR inf = GetMessageExtraInfo();

				if ((inf & 0x0FFFFFF00) != 0x0FF515700)
				{
					Vector2 pos(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)));

					//TODO: mouse buttons input
					if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
					{
					}
					else if (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP)
					{
					}
					else if (message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
					{
					}
					else if (message == WM_XBUTTONDOWN || message == WM_XBUTTONUP)
					{
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
						{

						}
						else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
						{

						}
						else
						{
						}
					}
					else
					{
					}

					if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_XBUTTONDOWN)
					{
						
					}
					else if (message == WM_LBUTTONUP || message == WM_RBUTTONUP || message == WM_MBUTTONUP || message == WM_XBUTTONUP)
					{
						
					}


					if (message == WM_XBUTTONDOWN || message == WM_XBUTTONUP)
					{

					}
				}
				break;

			}
			case WM_MOUSEMOVE:
			{
				LONG_PTR inf = GetMessageExtraInfo();

				if ((inf & 0x0FFFFFF00) != 0x0FF515700)
				{
					Vector2 pos(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)));

					//TODO: handle mouse move

				}
				break;
			}
			case WM_MOUSEWHEEL:
			case WM_MOUSEHWHEEL:
			{
				Vector2 pos(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)));

				if (message == WM_MOUSEWHEEL)
				{
					short param = static_cast<short>(HIWORD(wParam));
					//TODO: handle mouse wheel
				}
				else if (message == WM_MOUSEHWHEEL)
				{
					short param = static_cast<short>(HIWORD(wParam));
					//TODO: handle mouse wheel
				}

				break;
			}
			case WM_TOUCH:
			{
				//TODO: handle touch
				UINT inputCount = LOWORD(wParam);
				std::vector<TOUCHINPUT> touches(inputCount);

				if (GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(lParam), inputCount, touches.data(), sizeof(TOUCHINPUT)))
				{
					Vector2 position;

					for (const TOUCHINPUT& touch : touches)
					{
						position.x = static_cast<float>(touch.x / 100);
						position.y = static_cast<float>(touch.y / 100);

						if (touch.dwFlags & TOUCHEVENTF_DOWN)
						{

						}

						if (touch.dwFlags & TOUCHEVENTF_UP)
						{

						}

						if (touch.dwFlags & TOUCHEVENTF_MOVE)
						{

						}
					}

					if (!CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(lParam)))
					{

					}
				}
				else
				{

				}
				break;
			}
			case WM_SETCURSOR:
			{
				if (LOWORD(lParam) == HTCLIENT)
				{
					//TODO: process input;
					break;
				}
				break;
			}
			case WM_SIZE:
			{
				switch (wParam)
				{
					case SIZE_MINIMIZED:
						//TODO: Pause engine
						break;
					case SIZE_RESTORED:
						//TODO: Resume engine
						break;
					case SIZE_MAXIMIZED:
						win->ProcessResize(Vector2i(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam))));
						break;
				}
				break;
			}
			case WM_MOVE:
			{
				win->ProcessMove();
				break;
			}
			case WM_ERASEBKGND:
			{
				//TODO: erase bg for epmty engine
				break;
			}
			case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
					{
						//TODO: disable screen save if need
						break;
					}
					case SC_KEYMENU:
						break;
				}
				break;
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		}
		
		return DefWindowProcW(handle, message, wParam, lParam);
	}
}
