#include "OGLWIN32Context.h"
#include "Platform/Windows/WindowWin32.h"
#include "Platform/Engine.h"
#include "glad/glad_wgl.h"

namespace Forge
{

	OGLWIN32Context::OGLWIN32Context()
	{}


	OGLWIN32Context::~OGLWIN32Context()
	{}

	void OGLWIN32Context::Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer)
	{
		OGLContext::Init(win, sampleCount, depth, debugRenderer);

		WindowWin32* wnd = reinterpret_cast<WindowWin32*>(win.GetWindowImpl());

		deviceContext = GetDC(wnd->GetNativeWindow());

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
		pixelFormatDesc.cDepthBits = depth ? 24 : 0;
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
				WGL_DEPTH_BITS_ARB, depth ? 24 : 0,
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

		if (!gladLoadGL())
		{
			LOG("Failed to loat glad");
		}
	}

	void OGLWIN32Context::swapBuffers()
	{
		WindowWin32* winimp = static_cast<WindowWin32*>(engine->GetWindow().GetWindowImpl());
		SwapBuffers(GetDC(winimp->GetNativeWindow()));
	}

}
