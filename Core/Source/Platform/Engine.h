#pragma once
#include "Window.h"
#include "Graphics/Renderer.h"
#include "FileSystem/FileSystem.h"
#include "Game.h"


namespace Forge
{

	class Engine
	{
	protected:
		bool active;
		Renderer* renderer;
		Window* window;
		FileSystem* fileSystem;
		Game* game;
	public:

		Engine();

		void OpenWindow(const Vector2i& winSize, const String& title, bool fullScreen, bool HighDPI);
		void SetGame(Game* newGame);

		virtual void Init();
		FileSystem* GetFileSystem() { return fileSystem; }
		Window* GetWindow() { return window; }
		Renderer* GetRenderer() { return renderer; }

		virtual void Start();

		void Update();
	};

	extern Engine* engine;
}
