#include "OGLWIN32Context.h"
#include "Platform/Windows/WindowWin32.h"
#include "Core/Engine.h"
#include "glad/glad_wgl.h"

namespace Forge
{
	
	static const LPCWSTR windowClassName = L"TempWindow";
	static LRESULT CALLBACK windowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(window, msg, wParam, lParam);
	}
	
	OGLWIN32Context::OGLWIN32Context()
	{}

	//TODO: refactor creating off screen rendering context
	OGLWIN32Context::~OGLWIN32Context()
	{}

	void OGLWIN32Context::CreateContext(const Window& win, unsigned int sampleCount, bool debugRenderer)
	{
		const WindowWin32& wnd = reinterpret_cast<const WindowWin32&>(win);

        if(!gladLoadWGL(deviceContext))
        {
            CreateContext(sampleCount, debugRenderer);
            if(!gladLoadWGL(deviceContext))
            {
                LOG("Failed to load wgl");
            }
        }

		deviceContext = GetDC(wnd.GetNativeWindow());

		if (!deviceContext)
		{
			LOG("Failed to getDC");
			return;
		}

		int pixelFormat = 0;

		PIXELFORMATDESCRIPTOR pixelFormatDesc;
		pixelFormatDesc.nSize = sizeof(pixelFormatDesc);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 24;
		pixelFormatDesc.cRedBits = 0;
		pixelFormatDesc.cRedShift = 0;
		pixelFormatDesc.cGreenBits = 0;
		pixelFormatDesc.cGreenShift = 0;
		pixelFormatDesc.cBlueBits = 0;
		pixelFormatDesc.cBlueShift = 0;
		pixelFormatDesc.cAlphaBits = 0;
		pixelFormatDesc.cAlphaShift = 0;
		pixelFormatDesc.cAccumBits = 0;
		pixelFormatDesc.cAccumRedBits = 0;
		pixelFormatDesc.cAccumGreenBits = 0;
		pixelFormatDesc.cAccumBlueBits = 0;
		pixelFormatDesc.cAccumAlphaBits = 0;
		pixelFormatDesc.cDepthBits = 24;
		pixelFormatDesc.cStencilBits = 0;
		pixelFormatDesc.cAuxBuffers = 0;
		pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
		pixelFormatDesc.bReserved = 0;
		pixelFormatDesc.dwLayerMask = 0;
		pixelFormatDesc.dwVisibleMask = 0;
		pixelFormatDesc.dwDamageMask = 0;

		if (wglChoosePixelFormatARB)
		{
			const int attribs[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_SAMPLE_BUFFERS_ARB, sampleCount > 0 ? 1 : 0,
				WGL_SAMPLES_ARB, static_cast<int>(sampleCount),
				0,
			};

			UINT numFormats;

			if (!wglChoosePixelFormatARB(deviceContext, attribs, nullptr, 1, &pixelFormat, &numFormats))
			{
				LOG("Failed to choose pixel fromat");
				return;
			}
		}
		else
		{
			pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
		}
        
		if (!pixelFormat)
		{
			LOG("Failed to choose pixel fromat");
			return;
		}

		if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
		{
			LOG("Failed to set pixel fromat");
			return;
		}

		if (wglCreateContextAttribsARB)
		{
			for (int i = 4; i >= 2 ; --i)
			{
				std::vector<int> contextAttrs =
				{
					WGL_CONTEXT_MAJOR_VERSION_ARB, i, WGL_CONTEXT_MINOR_VERSION_ARB, 0
				};

				if (debugRenderer)
				{
					contextAttrs.push_back(WGL_CONTEXT_FLAGS_ARB);
					contextAttrs.push_back(WGL_CONTEXT_DEBUG_BIT_ARB);
				}

				contextAttrs.push_back(0);

				renderContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttrs.data());

				if (renderContext)
				{
					LOG(String("Opengl " + String(i) + " version context created").CString());
					break;
				}
			}
		}
		else
		{
			renderContext = wglCreateContext(deviceContext);
		}

		if (!renderContext)
		{
			LOG("Failed to create OpenGL context");
			return;
		}

		if (!wglMakeCurrent(deviceContext, renderContext))
		{
			LOG("Failed to set current OpenGL context");
			return;
		}
	}

	void OGLWIN32Context::CreateContext(unsigned sampleCount, bool debugRenderer)
	{
		HINSTANCE hInstance = GetModuleHandleW(nullptr);

		WNDCLASSW wc;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = windowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = 0;
		wc.hCursor = 0;
		wc.hbrBackground = 0;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = windowClassName;

		windowClass = RegisterClassW(&wc);

		if (!windowClass)
		{
			LOG("Failed to register window class");
			return;
		}

		window = CreateWindowW(windowClassName, L"TempWindow", 0,
							   CW_USEDEFAULT, CW_USEDEFAULT,
							   CW_USEDEFAULT, CW_USEDEFAULT,
							   0, 0, hInstance, 0);

		if (!window)
		{
			LOG("Failed to create window");
			return;
		}

		deviceContext = GetDC(window);

		int pixelFormat = 0;

		PIXELFORMATDESCRIPTOR pixelFormatDesc;
		pixelFormatDesc.nSize = sizeof(pixelFormatDesc);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 24;
		pixelFormatDesc.cRedBits = 0;
		pixelFormatDesc.cRedShift = 0;
		pixelFormatDesc.cGreenBits = 0;
		pixelFormatDesc.cGreenShift = 0;
		pixelFormatDesc.cBlueBits = 0;
		pixelFormatDesc.cBlueShift = 0;
		pixelFormatDesc.cAlphaBits = 0;
		pixelFormatDesc.cAlphaShift = 0;
		pixelFormatDesc.cAccumBits = 0;
		pixelFormatDesc.cAccumRedBits = 0;
		pixelFormatDesc.cAccumGreenBits = 0;
		pixelFormatDesc.cAccumBlueBits = 0;
		pixelFormatDesc.cAccumAlphaBits = 0;
		pixelFormatDesc.cDepthBits = 24;
		pixelFormatDesc.cStencilBits = 0;
		pixelFormatDesc.cAuxBuffers = 0;
		pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
		pixelFormatDesc.bReserved = 0;
		pixelFormatDesc.dwLayerMask = 0;
		pixelFormatDesc.dwVisibleMask = 0;
		pixelFormatDesc.dwDamageMask = 0;

		if (wglChoosePixelFormatARB)
		{
			const int attribs[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_SAMPLE_BUFFERS_ARB, sampleCount > 0 ? 1 : 0,
				WGL_SAMPLES_ARB, static_cast<int>(sampleCount),
				0,
			};

			UINT numFormats;

			if (!wglChoosePixelFormatARB(deviceContext, attribs, nullptr, 1, &pixelFormat, &numFormats))
			{
				LOG("Failed to choose pixel fromat");
				return;
			}
		}
		else
		{
			pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
		}

		if (!pixelFormat)
		{
			LOG("Failed to choose pixel fromat");
			return;
		}

		if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
		{
			LOG("Failed to set pixel fromat");
			return;
		}

		if (wglCreateContextAttribsARB)
		{
			for (int i = 4; i >= 2; --i)
			{
				std::vector<int> contextAttrs =
				{
					WGL_CONTEXT_MAJOR_VERSION_ARB, i, WGL_CONTEXT_MINOR_VERSION_ARB, 0
				};

				if (debugRenderer)
				{
					contextAttrs.push_back(WGL_CONTEXT_FLAGS_ARB);
					contextAttrs.push_back(WGL_CONTEXT_DEBUG_BIT_ARB);
				}

				contextAttrs.push_back(0);

				renderContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttrs.data());

				if (renderContext)
				{
					LOG(String("Opengl " + String(i) + " version context created").CString());
					break;
				}
			}
		}
		else
		{
			renderContext = wglCreateContext(deviceContext);
		}

		if (!renderContext)
		{
			LOG("Failed to create OpenGL context");
			return;
		}

		if (!wglMakeCurrent(deviceContext, renderContext))
		{
			LOG("Failed to set current OpenGL context");
			return;
		}
	}

	void OGLWIN32Context::DeleteContext()
	{
		//delete cont;
	}

	void OGLWIN32Context::SendMsg(const int* hwnd, int msg, const int wParam, const int lParam)
	{
		SendMessageW((HWND)hwnd, msg, (WPARAM)wParam, (LPARAM)lParam);
	}

	void OGLWIN32Context::PlatformUpdate()
	{
		SwapBuffers(deviceContext);
		
		MSG message;
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
}
