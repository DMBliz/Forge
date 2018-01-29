#include "Engine.h"
#include "Utilities/Timer.h"

namespace Forge
{
	Forge::Engine* engine = nullptr;

	Engine::Engine()
	{
		engine = this;
		fileSystem = new FileSystem();
		renderer = new Renderer();
		context = Context::Create();
		input = Input::Create();
	}

	void Engine::Init()
	{
		active = true;
		paused = false;
		context->CreateContext(*window, 1, false, false);
		renderer->Init(window);
		
	}

	void Engine::Start()
	{
		Init();
		Timer::StartTime();
		game->Initialize();
		Update();
	}

	void Engine::Update()
	{
		while (active)
		{
			context->PlatformUpdate();
			if (!paused)
			{
				Timer::BeginFrame();
				input->Update();
				game->Update();
				renderer->Draw();
				Timer::EndFrame();
				
			}
		}
	}

	void Engine::Pause()
	{
		//paused = true;
	}

	void Engine::Resume()
	{
		//paused = false;
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

