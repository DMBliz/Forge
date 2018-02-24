#pragma once
#include "Platform/Window.h"
#include "Graphics/Renderer.h"
#include "FileSystem/FileSystem.h"
#include "Game.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Resources/Resources.h"


namespace Forge
{

	class Engine
	{
	protected:
		bool active;
		bool paused;
		bool hasWindow = true;
		Renderer* renderer;
		Window* window;
		FileSystem* fileSystem;
		Input* input;
		Scene* scene;
		Resources* resources;
	public:

		Engine();

		void OpenWindow(const Vector2i& winSize, const String& title, bool fullScreen, bool HighDPI);

		void Init();
		Resources* GetResources() const { return resources; }
		FileSystem* GetFileSystem() const { return fileSystem; }
		Input* GetInputSystem() const { return input; }
		Window* GetWindow() const { return window; }
		Renderer* GetRenderer() const { return renderer; }
		Scene* GetScene() const { return scene; }

		void Start();
		void ShutDown() { active = false; }

		void MainLoop();
		void Update();


		void Pause();
		void Resume();

		bool IsActive();
	};

	extern Engine* engine;
}
