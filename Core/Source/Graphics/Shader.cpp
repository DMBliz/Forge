#include "Shader.h"
#include <fstream>
#include "OpenGL/OGLShader.h"

namespace Forge
{

	Shader::Shader()
	{}

	Shader* Shader::Create()
	{
#if defined(OGL)
		return new OGLShader();
#elif defined(DX) //TODO: Returen shader for DX
		return null;
#endif
	}
}
