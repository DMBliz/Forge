#pragma once
#include "Graphics/Context.h"
#include "windows.h"

namespace Forge
{

	class OGLWIN32Context : public Context
	{
	private:
		HDC deviceContext = 0;
		HGLRC renderContext = 0;
	public:
		OGLWIN32Context();
		~OGLWIN32Context();

		void CreateContext(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer) override;
		void PlatformUpdate() override;

	};

}
