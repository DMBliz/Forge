#pragma once

namespace Forge
{
	class Window;

	class Context
	{
	public:
	    virtual void init(Window& win, unsigned int sampleCount) = 0;
		virtual void deleteContext() = 0;
		virtual void platformUpdate() = 0;
		virtual void setActive() = 0;
	};

}
