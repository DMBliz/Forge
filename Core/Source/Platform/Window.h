#pragma once
#include "WindowImpl.h"

namespace Forge
{

	class Window
	{
	private:
		WindowImpl* window;
	public:
		Window();
		~Window();

		WindowImpl* GetWindowImpl() const
		{
			return window;
		}

		void Init();

		const Vector2i& GetWindowSize() const
		{
			return window->GetSize();
		}

		void Create(const Vector2i& size, const String& title, bool fullScreen)
		{
			window->Create(size, title, true, fullScreen, fullScreen, true, true);
		}
	};

}
