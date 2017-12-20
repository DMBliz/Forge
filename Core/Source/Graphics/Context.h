#pragma once

namespace Forge
{
	class Window;

	class Context
	{
	public:
		static Context* GetInstance();
		virtual void CreateContext(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer) = 0;
		virtual void PlatformUpdate() = 0;
	};

}
