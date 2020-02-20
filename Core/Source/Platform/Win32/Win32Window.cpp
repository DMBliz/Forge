#include "Win32Window.h"
#include "Containers/String.h"
#include "Math/Vector2.h"
#include <windowsx.h>
#include "Defines.h"
#include "Core/Engine.h"
#include "Platform/Win32/Win32Input.h"
#include "glad/glad_wgl.h"


namespace Forge
{
	const wchar_t* classname = L"ForgeWindow";

	
	Win32Window::Win32Window()
	{
	    winInput.setPosition = Delegate<void(const Vector2i&)>::create<Win32Window, &Win32Window::setCursorPosition>(this);
	}

	Win32Window::~Win32Window()
	{
		
	}

    void Win32Window::create(const WindowCreationDesc &creationDesc)
    {
        this->windowRect = creationDesc.size;
        this->windowTitle = creationDesc.title;
        this->resizable = creationDesc.resizable;
        this->windowState = creationDesc.openState;
        this->highDPI = creationDesc.highDPI;

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

        if (resizable)
            _windowWindowedStyle |= WS_SIZEBOX | WS_MAXIMIZEBOX;

        _wdindowFullScreenStyle = WS_CLIPSIBLINGS | WS_GROUP | WS_TABSTOP;

        int x = CW_USEDEFAULT;
        int y = CW_USEDEFAULT;

        _windowStyle = _windowWindowedStyle;
        _windowExStyle = WS_EX_APPWINDOW;

        RECT nativeRect = {windowRect.x, windowRect.x, static_cast<LONG>(windowRect.width), static_cast<LONG>(windowRect.height) };
        AdjustWindowRectEx(&nativeRect, _windowStyle, FALSE, _windowExStyle);

        int width = CW_USEDEFAULT;
        int height = CW_USEDEFAULT;

        if (windowRect.width > 0.0f)
            width = nativeRect.right - nativeRect.left;
        if (windowRect.height > 0.0f)
            height = nativeRect.bottom - nativeRect.top;


        wchar_t titleBuff[256] = L"Window";
        if (!windowTitle.IsEmpty())
        {
            WString tmp(windowTitle);
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

        if (windowState == WindowState::FULLSCREEN)
            setWindowState(windowState);

        GetClientRect(_hwnd, &nativeRect);

        windowRect.x = nativeRect.right - nativeRect.left;
        windowRect.y = nativeRect.bottom - nativeRect.top;
        resolution = windowRect.size();

        if (!RegisterTouchWindow(_hwnd, SW_SHOW))
        {
            LOG_WARN("cant register touch window");
        }
        ShowWindow(_hwnd, SW_SHOW);

        SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    }

	void Win32Window::setWindowRect(const RectI& newSize)
	{
		Window::setWindowRect(newSize);

		RECT rect = { 0, 0, static_cast<LONG>(newSize.x), static_cast<LONG>(newSize.y) };
		AdjustWindowRectEx(&rect, _windowStyle, GetMenu(_hwnd) ? TRUE : FALSE, _windowExStyle);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		SetWindowPos(_hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

		resolution = windowRect.size();
	}

	void Win32Window::setTitle(const String& newTitle)
	{
		if(windowTitle == newTitle)
			return;

		SetWindowTextW(_hwnd, WString(windowTitle).CString());
		Window::setTitle(newTitle);
	}

	void Win32Window::setWindowState(WindowState windowState)
	{
		Window::setWindowState(windowState);

		switch (windowState)
        {
            case WindowState::FULLSCREEN:
                break;
            case WindowState::WINDOWED:
                break;
            case WindowState::MAXIMIZED:
                _windowStyle = _windowWindowedStyle;
                SetWindowLong(_hwnd, GWL_STYLE, _windowStyle);

                RECT rect;
                GetWindowRect(_hwnd, &rect);

                windowedPos.Set(static_cast<int>(rect.left), static_cast<int>(rect.top));
                windowedSize.Set(static_cast<int>(rect.right), static_cast<int>(rect.bottom));

                resolution = windowRect.size();
                break;
        }
	}

	void Win32Window::close()
	{
		SendMessage(_hwnd, WM_CLOSE, 0, 0);
	}

	void Win32Window::platformUpdate()
	{
		MSG message;
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

	void Win32Window::setClipboard(const String& data)
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

	const String& Win32Window::getClipboard()
	{
		return static_cast<char*>(GetClipboardData(CF_TEXT));
	}

	void Win32Window::setCursorPosition(const Vector2i& newPos)
	{
		POINT pos = { newPos.x, newPos.y };
		ClientToScreen(_hwnd, &pos);
		SetCursorPos(pos.x, pos.y);
	}

	void Win32Window::ProcessResize(const Vector2i& size)
	{
		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);

        windowRect.width = size.x;
        windowRect.height = size.y;

		onSizeChanged.Invoke(this, size);
	}

	void Win32Window::ProcessMove()
	{
		_monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);
	}

	LRESULT CALLBACK Win32Window::WindProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* win = reinterpret_cast<Forge::Win32Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));

		if (!win)
			return DefWindowProcW(handle, message, wParam, lParam);

		switch (message)
		{
			case WM_ACTIVATEAPP:
			{
				if (wParam)
				{
					//resume engine work
					
					win->hasFocus = true;
				}
				else
				{
					//pause engine work
					win->hasFocus = false;
				}
				break;
			}
			case WM_CHAR:
			case WM_SYSCHAR:
			case WM_UNICHAR:
			{
				bool plain = (message != WM_SYSCHAR);
                win->getInput()->SetCharacterPressed(static_cast<uint>(wParam));
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
                    win->getInput()->SetKeyDownNative(key);
				}
				else if (message == WM_KEYUP)
				{
                    win->getInput()->SetKeyUpNative(key);
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
						Win32Input* t = win->getInput();
						t->SetButtonDownNative(button);
						t->SetMousePositionValue(pos);
					}
					else if (message == WM_LBUTTONUP || message == WM_RBUTTONUP || message == WM_MBUTTONUP || message == WM_XBUTTONUP)
					{
						Win32Input* t = win->getInput();
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
                    win->getInput()->SetMousePositionValue(pos);
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
                    win->getInput()->SetScrollNative(
						Vector2(0.0f, static_cast<float>(param) / static_cast<float>(WHEEL_DELTA)));
					//TODO: handle mouse wheel
				}
				else if (message == WM_MOUSEHWHEEL)
				{
					short param = static_cast<short>(HIWORD(wParam));
                    win->getInput()->SetScrollNative(
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
//						engine->Pause();
						break;
					case SIZE_RESTORED:
						//Resume engine
//						engine->Resume();
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

    void Win32Window::show() {

    }

    void Win32Window::hide() {

    }

    Win32Input* Win32Window::getInput()
    {
        return &winInput;
    }
}
