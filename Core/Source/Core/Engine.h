#pragma once
#include "Platform/Window.h"
#include "Graphics/Renderer.h"
#include "FileSystem/FileSystem.h"
#include "Game.h"
#include "Input/Input.h"



namespace Forge
{

	class Engine
	{
	protected:
		bool active;
		bool paused;
		Renderer* renderer;
		Window* window;
		FileSystem* fileSystem;
		Input* input;
		Game* game;
		Context* context;
	public:

		Engine();

		void OpenWindow(const Vector2i& winSize, const String& title, bool fullScreen, bool HighDPI);
		void SetGame(Game* newGame);

		void Init();
		FileSystem* GetFileSystem() { return fileSystem; }
		Input* GetInputSystem() { return input; }
		Window* GetWindow() { return window; }
		Renderer* GetRenderer() { return renderer; }

		void Start();
		void ShutDown() { active = false; }

		void Update();

		void Pause();
		void Resume();
	};

	extern Engine* engine;
}
