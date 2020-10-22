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

	void Engine::init(Application* application)
	{
	    this->application = application;
        application->getPlatformApiProvider()->init();
        resources = new Resources();
        fileSystem = new MacOSFileSystem();

		active = true;
		Timer::StartTime();
	}

	void Engine::start()
	{
		application->start();
        mainLoop();
	}

	void Engine::mainLoop()
	{
		while (active)
		{
            update();
		}
	}

	void Engine::update()
	{
		if (active)
		{
			Timer::BeginFrame();
			application->update();
            application->draw();
			Timer::EndFrame();
		}
	}

	bool Engine::isActive()
	{
		return active;
	}

    void Engine::shutDown()
    {
        active = false;
        application->stop();
    }

    Application* Engine::getApplication() const
    {
        return application;
    }
}

