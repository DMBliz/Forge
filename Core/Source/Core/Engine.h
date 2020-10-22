#pragma once

#include "Platform/Api/WindowSystem.h"
#include "Platform/Api/Window.h"
#include "Graphics/Renderer.h"
#include "Platform/Api/FileSystem.h"
#include "Scene/Scene.h"
#include "Resources/Resources.h"
#include "Platform/Application.h"

namespace Forge
{

	class Engine
	{
	protected:
		bool active;
		Application* application;
		Renderer* renderer;
        WindowSystem* windowSystem;
		FileSystem* fileSystem;
		Scene* scene;
		Resources* resources;
	public:

		Engine();

		void init(Application* application);
		Application* getApplication() const;
		Resources* getResources() const { return resources; }
		FileSystem* getFileSystem() const { return fileSystem; }
		WindowSystem* getWindow() const { return windowSystem; }
        Scene* getScene() const { return scene; }

        Renderer* getRenderer() const { return renderer; }
        void setRender(Renderer* render)
		{
			renderer = render;
		}

		void start();
		void shutDown();

		void mainLoop();
		void update();

		bool isActive();
	};

	extern Engine* engine;
}
