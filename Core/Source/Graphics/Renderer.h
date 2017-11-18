#pragma once
#include "Context.h"

namespace Forge
{
	class Window;

	class Renderer
	{
	private:
		Context* singleton;
	public:

		static Renderer* GetRenderer()
		{
			Renderer* rend = new Renderer();
			return rend;
		}
		
		virtual void Init(Window win);

		virtual void Draw()
		{
			singleton->Draw();
			singleton->swapBuffers();
		}

		Renderer();
		~Renderer();
	};

}
