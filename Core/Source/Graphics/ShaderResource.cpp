#include "ShaderResource.h"
#include <fstream>
#include "OGL/GLShaderResource.h"

namespace Forge
{

	ShaderResource* ShaderResource::Create()
	{
#if defined(OGL)
		return new GLShaderResource();
#elif defined(DX) //TODO: Returen shader for DX
		return null;
#endif
	}
}
