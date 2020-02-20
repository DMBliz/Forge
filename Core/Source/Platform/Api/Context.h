#pragma once

namespace Forge
{
	class Window;

	class Context
	{
	public:
		virtual void CreateContext(Window& win, unsigned int sampleCount) = 0;
		virtual void DeleteContext() = 0;
		virtual void PlatformUpdate() = 0;
		virtual void setActive() = 0;
	};

}
