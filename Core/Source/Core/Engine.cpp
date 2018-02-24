#include "Engine.h"
#include "Utilities/Timer.h"

namespace Forge
{
	Forge::Engine* engine = nullptr;

	Engine::Engine()
	{
		engine = this;
		scene = new Scene();
	}

	void Engine::Init()
	{
		fileSystem = FileSystem::Create();
		renderer = new Renderer();
		resources = new Resources();
		input = Input::Create();
		window = Window::GetInstance();

		active = true;
		paused = false;

		window->CreateContext();
		renderer->Init(Vector2i(800, 600));
		Timer::StartTime();
	}

	void Engine::Start()
	{
		//Init();
		MainLoop();
	}

	void Engine::MainLoop()
	{
		while (active)
		{
			Update();
		}
	}

	void Engine::Update()
	{
		window->PlatformUpdate();
		if (!paused)
		{
			Timer::BeginFrame();
			input->Update();
			scene->Update();
			renderer->Draw();
			resources->Update();
			Timer::EndFrame();
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

	bool Engine::IsActive()
	{
		return active;
	}

	void Engine::OpenWindow(const Vector2i& winSize, const String& title, bool fullScreen, bool HighDPI)
	{
		window->Create(winSize, title, true, fullScreen, fullScreen, HighDPI, true);
		renderer->Init(winSize);
	}
}

