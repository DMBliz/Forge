#include "OGLWin32Context.h"
#include "Platform/Win32/Win32Window.h"
#include "Core/Engine.h"
#include "glad/glad_wgl.h"

namespace Forge
{
	OGLWin32Context::OGLWin32Context()
	{}

    OGLWin32Context::~OGLWin32Context()
	{}

	LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		switch (message) {
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0);
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;       // message handled
	}

	bool OGLWin32Context::loadGladWithTempWindow()
	{
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowProcedure;
		wcex.hInstance = GetModuleHandleW(nullptr);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = "Core";

		LPCSTR atm = MAKEINTATOM(RegisterClassEx(&wcex));
		DWORD style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		HWND fakeWND = CreateWindow(
			atm, "Fake Window",
			style,
			0, 0,						// position x, y
			1, 1,						// width, height
			NULL, NULL,					// parent window, menu
			GetModuleHandleW(nullptr), NULL);			// instance, param

		HDC fakeDC = GetDC(fakeWND);	// Device Context

		PIXELFORMATDESCRIPTOR fakePFD;
		ZeroMemory(&fakePFD, sizeof(fakePFD));
		fakePFD.nSize = sizeof(fakePFD);
		fakePFD.nVersion = 1;
		fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		fakePFD.iPixelType = PFD_TYPE_RGBA;
		fakePFD.cColorBits = 32;
		fakePFD.cAlphaBits = 8;
		fakePFD.cDepthBits = 24;

		const int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
		if (fakePFDID == 0) 
		{
			ReleaseDC(fakeWND, fakeDC);
			DestroyWindow(fakeWND);
			LOG_ERROR("ChoosePixelFormat() failed.");
			return false;
		}

		if (SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false) 
		{
			ReleaseDC(fakeWND, fakeDC);
			DestroyWindow(fakeWND);
			LOG_ERROR("SetPixelFormat() failed.");
			return false;
		}

		HGLRC fakeRC = wglCreateContext(fakeDC);	// Rendering Contex

		if (fakeRC == 0) 
		{
			ReleaseDC(fakeWND, fakeDC);
			DestroyWindow(fakeWND);
			LOG_ERROR("wglCreateContext() failed.");
			return false;
		}

		if (wglMakeCurrent(fakeDC, fakeRC) == false) 
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(fakeRC);
			ReleaseDC(fakeWND, fakeDC);
			DestroyWindow(fakeWND);
			LOG_ERROR("wglMakeCurrent() failed.");
			return false;
		}

		if (!gladLoadWGL(fakeDC))
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(fakeRC);
			ReleaseDC(fakeWND, fakeDC);
			DestroyWindow(fakeWND);
			return false;
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeRC);
		ReleaseDC(fakeWND, fakeDC);
		DestroyWindow(fakeWND);

		return true;
	}

	void OGLWin32Context::CreateContext(Window& win, unsigned int sampleCount)
	{
		const Win32Window& wnd = reinterpret_cast<const Win32Window&>(win);

		deviceContext = GetDC(wnd.GetNativeWindow());

        if(!gladLoadWGL(deviceContext))
        {
			if (!loadGladWithTempWindow())
			{
				LOG_ERROR("Failed to load wgl");
				return;
			}
        }

		if (!deviceContext)
		{
			LOG_ERROR("Failed to getDC");
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
				LOG_ERROR("Failed to choose pixel fromat");
				return;
			}
		}
		else
		{
			pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
		}
        
		if (!pixelFormat)
		{
			LOG_ERROR("Failed to choose pixel fromat");
			return;
		}

		if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
		{
			LOG_ERROR("Failed to set pixel fromat");
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

				contextAttrs.push_back(0);

				renderContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttrs.data());

				if (renderContext)
				{
					LOG_INFO(String("Opengl " + String(i) + " version context created").CString());
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
			LOG_ERROR("Failed to create OpenGL context");
			return;
		}

		if (!wglMakeCurrent(deviceContext, renderContext))
		{
			LOG_ERROR("Failed to set current OpenGL context");
			return;
		}
	}

	void OGLWin32Context::DeleteContext()
	{
		//delete cont;
	}

	void OGLWin32Context::PlatformUpdate()
	{
		SwapBuffers(deviceContext);
	}

    void OGLWin32Context::setActive()
    {
        wglMakeCurrent(deviceContext, renderContext);
    }
}
