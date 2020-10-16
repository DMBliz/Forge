#include "Platform/MacOS/MacOSFileSystem.h"
#include "Engine.h"
#include "Utilities/Timer.h"
#include "Platform/Api/PlatformApiProvider.h"

namespace Forge
{
	Forge::Engine* engine = nullptr;

	Engine::Engine()
	{
		engine = this;
	}

	void Engine::Init(Application* application)
	{
	    this->application = application;
        application->getPlatformApiProvider()->init();
        resources = new Resources();
        fileSystem = new MacOSFileSystem();

		active = true;
		Timer::StartTime();
	}

	void Engine::Start()
	{
		application->start();
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
		if (active)
		{
			Timer::BeginFrame();
			application->update();
			Timer::EndFrame();
		}
	}

	bool Engine::IsActive()
	{
		return active;
	}

    void Engine::ShutDown()
    {
        active = false;
        application->stop();
    }

    Application* Engine::getApplication() const
    {
        return application;
    }
}

