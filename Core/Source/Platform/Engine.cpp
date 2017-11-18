#include "Engine.h"

namespace Forge
{
	Forge::Engine* engine = nullptr;

	Engine::Engine()
	{
		engine = this;
		renderer = Renderer::GetRenderer();
	}

	void Engine::Update()
	{
		while (active)
		{

			PlatrformUpdate();
			renderer->Draw();
		}
	}

	void Engine::Init()
	{
		window.Init();
		window.Create(Vector2i(800, 600), "New testing Forge window", true);
		renderer->Init(window);
	}

}

