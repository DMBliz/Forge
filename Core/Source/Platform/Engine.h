#pragma once
#include "Window.h"
#include "Graphics/Renderer.h"


namespace Forge
{

	class Engine
	{
	protected:
		bool active;
		Renderer* renderer;
		Window window;
	public:

		Engine();

		Window GetWindow() { return window; }

		virtual void Init();

		virtual void Start() = 0;

		void Update();

		virtual void PlatrformUpdate() = 0;
	};

	extern Engine* engine;
}
