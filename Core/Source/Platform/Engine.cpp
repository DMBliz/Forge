#include "Engine.h"

namespace Forge
{
	Forge::Engine* engine = nullptr;

	Engine::Engine()
	{
		engine = this;
		fileSystem = new FileSystem();
		renderer = Renderer::GetRenderer();
	}

	void Engine::Init()
	{
		active = true;
		renderer->Init(window);
	}

	void Engine::Start()
	{
		Init();
		game->Initialize();
		Update();
	}

	void Engine::Update()
	{
		while (active)
		{
			renderer->Draw();
			game->Update();
		}
	}

	void Engine::OpenWindow(const Vector2i& winSize, const String& title, bool fullScreen, bool HighDPI)
	{
		window = Window::GetInstance();
		window->Create(winSize, title, true, fullScreen, fullScreen, HighDPI, true);
	}

	void Engine::SetGame(Game* newGame)
	{
		game = newGame;
	}
}

