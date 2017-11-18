#pragma once
#include "Graphics/OpenGL/OGLContext.h"
#include "windows.h"

namespace Forge
{

	class OGLWIN32Context : public OGLContext
	{
	private:
		HDC deviceContext = 0;
		HGLRC renderContext = 0;
	public:
		OGLWIN32Context();
		~OGLWIN32Context();

		void Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer) override;

		void swapBuffers() override;

	};

}
