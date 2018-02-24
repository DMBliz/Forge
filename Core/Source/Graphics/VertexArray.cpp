#include "VertexArray.h"
#include "OpenGL/GLVertexArray.h"

namespace Forge
{
	VertexArray* VertexArray::Create()
	{
#if defined(OGL)
		return new GLVertexArray();
#elif defined(DX)
#endif
	}
}

