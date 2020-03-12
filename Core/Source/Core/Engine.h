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

		void Init(Application* application);
		Application* getApplication() const;
		Resources* GetResources() const { return resources; }
		FileSystem* GetFileSystem() const { return fileSystem; }
		WindowSystem* GetWindow() const { return windowSystem; }
		Renderer* GetRenderer() const { return renderer; }
		Scene* GetScene() const { return scene; }
		void setRender(Renderer* render)
		{
			renderer = render;
		}

		void Start();
		void ShutDown();

		void MainLoop();
		void Update();

		bool IsActive();
	};

	extern Engine* engine;
}
