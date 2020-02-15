#include "Win32Window.h"
#include "Containers/String.h"
#include "Math/Vector2.h"
#include <Windowsx.h>
#include "Defines.h"
#include "Core/Engine.h"
#include "Input/Windows/WIN32Input.h"
#include "glad/glad_wgl.h"


namespace Forge
{
	const wchar_t* classname = L"ForgeWindow";

	
	WindowWin32::WindowWin32()
	{
		context = Context::Create();
	}

	WindowWin32::~WindowWin32()
	{
		
	}

	void WindowWin32::Create(const Vector2i& size, const String& title, bool Resizable, bool FullScreen, 
							 bool ExclusiveFullScreen, bool HighDPI, bool depth)
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
			LOG_ERROR("can't register window class");
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
			LOG_ERROR("can't create window");
			return;
		}

		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);

		if (fullScreen)
			SetFullScreen(fullScreen);

		GetClientRect(_hwnd, &windowRect);
		
		windowSize.x = windowRect.right - windowRect.left;
		windowSize.y = windowRect.bottom - windowRect.top;
		framebufferSize.Set(static_cast<int>(windowRect.right), static_cast<int>(windowRect.bottom));
		windowResolution = windowSize;

		if (!RegisterTouchWindow(_hwnd, SW_SHOW))
		{
			LOG_WARN("cant register touch window");
		}
		ShowWindow(_hwnd, SW_SHOW);

		SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		context->CreateContext(*this, 0, 0);
	}

	void WindowWin32::CreateContext()
	{
		context->CreateContext(0, 0);
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

		onSizeChanged(windowSize);
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
				windowedSize.Set(static_cast<int>(rect.right), static_cast<int>(rect.bottom));
				framebufferSize.Set(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));

				windowResolution = windowSize;


				onSizeChanged(windowSize);
			}
		}
	}

	void WindowWin32::Close()
	{
		SendMessage(_hwnd, WM_CLOSE, 0, 0);
	}

	void WindowWin32::PlatformUpdate()
	{
		context->PlatformUpdate();
	}

	void WindowWin32::SetClipboard(const String& data)
	{
		if (!OpenClipboard(_hwnd))
			return;
		if (!EmptyClipboard())
			return;

		HGLOBAL hgl = GlobalAlloc(GMEM_FIXED, data.Length() + 1);
		char* buffer = static_cast<char*>(GlobalLock(hgl));
		memcpy(buffer, data.CString(), data.Length());

		GlobalUnlock(hgl);

		SetClipboardData(CF_TEXT, buffer);

		CloseClipboard();
	}

	const String& WindowWin32::GetClipboard()
	{
		return static_cast<char*>(GetClipboardData(CF_TEXT));
	}

	void WindowWin32::SetCursorPosition(const Vector2i& newPos)
	{
		POINT pos = { newPos.x, newPos.y };
		ClientToScreen(_hwnd, &pos);
		SetCursorPos(pos.x, pos.y);
	}

	void WindowWin32::ProcessResize(const Vector2i& size)
	{
		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);

		windowSize = size;

		onSizeChanged.Invoke(windowSize);
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
					//resume engine work
					engine->Resume();
					
					win->hasFocus = true;
				}
				else
				{
					//pause engine work
					engine->Pause();
					win->hasFocus = false;
				}
				break;
			}
			case WM_CHAR:
			case WM_SYSCHAR:
			case WM_UNICHAR:
			{
				bool plain = (message != WM_SYSCHAR);

				static_cast<WinInput*>(engine->GetInputSystem())->SetCharacterPressed(static_cast<uint>(wParam));
				return 0;
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
					static_cast<WinInput*>(engine->GetInputSystem())->SetKeyDownNative(key);
				}
				else if (message == WM_KEYUP)
				{
					static_cast<WinInput*>(engine->GetInputSystem())->SetKeyUpNative(key);
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

					MouseButton button;
					if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
					{
						button = MouseButton::Left;
					}
					else if (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP)
					{
						button = MouseButton::Right;
					}
					else if (message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
					{
						button = MouseButton::Middle;
					}
					else if (message == WM_XBUTTONDOWN || message == WM_XBUTTONUP)
					{
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
							button = MouseButton::XButton1;
						else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
							button = MouseButton::XButton2;
						else
							break;
					}
					else
					{
						break;
					}

					if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_XBUTTONDOWN)
					{
						WinInput* t = static_cast<WinInput*>(engine->GetInputSystem());
						t->SetButtonDownNative(button);
						t->SetMousePositionValue(pos);
					}
					else if (message == WM_LBUTTONUP || message == WM_RBUTTONUP || message == WM_MBUTTONUP || message == WM_XBUTTONUP)
					{
						WinInput* t = static_cast<WinInput*>(engine->GetInputSystem());
						t->SetButtonUpNative(button);
						t->SetMousePositionValue(pos);
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
					static_cast<WinInput*>(engine->GetInputSystem())->SetMousePositionValue(pos);
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
					static_cast<WinInput*>(engine->GetInputSystem())->SetScrollNative(
						Vector2(0.0f, static_cast<float>(param) / static_cast<float>(WHEEL_DELTA)));
					//TODO: handle mouse wheel
				}
				else if (message == WM_MOUSEHWHEEL)
				{
					short param = static_cast<short>(HIWORD(wParam));
					static_cast<WinInput*>(engine->GetInputSystem())->SetScrollNative(
						Vector2(static_cast<float>(param) / static_cast<float>(WHEEL_DELTA), 0.0f));
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
						//Pause engine
						engine->Pause();
						break;
					case SIZE_RESTORED:
						//Resume engine
						engine->Resume();
						break;
					case SIZE_MAXIMIZED:
						win->ProcessResize(Vector2i(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam))));
						break;
						
				}
				win->ProcessResize(Vector2i(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam))));
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
			case WM_CLOSE:
			{
				engine->ShutDown();
			}
		}
		
		return DefWindowProcW(handle, message, wParam, lParam);
	}
}
