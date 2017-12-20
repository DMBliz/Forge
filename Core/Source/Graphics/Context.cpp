#include "Context.h"
#include "OpenGL/Windows/OGLWIN32Context.h"

namespace Forge
{
	Context* Context::GetInstance()
	{
		Context* ret;
#if defined(WIN32)
#if defined(OGL)
		ret = new OGLWIN32Context();
#elif defined(DIRECTX)
#endif
#elif defined(MACOS)
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		return ret;
	}
}
