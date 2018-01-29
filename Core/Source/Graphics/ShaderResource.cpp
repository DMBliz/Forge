#include "ShaderResource.h"
#include <fstream>
#include "OpenGL/OGLShaderResource.h"

namespace Forge
{

	ShaderResource* ShaderResource::Create()
	{
#if defined(OGL)
		return new OGLShaderResource();
#elif defined(DX) //TODO: Returen shader for DX
		return null;
#endif
	}
}
