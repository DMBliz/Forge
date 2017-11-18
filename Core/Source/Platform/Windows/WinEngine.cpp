#include "WinEngine.h"
#include "glad/glad.h"
#include "glad/glad_wgl.h"
#include "Graphics/Renderer.h"
#include "WindowWin32.h"
#include "Defines.h"


namespace Forge
{

	WinEngine::WinEngine() : Engine()
	{}


	WinEngine::~WinEngine()
	{}

	void WinEngine::Init()
	{
		Engine::Init();
	}

	void WinEngine::Start()
	{
		active = true;

	}

	void WinEngine::PlatrformUpdate()
	{
		MSG message;
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

}
