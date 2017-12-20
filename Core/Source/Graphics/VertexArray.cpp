#include "VertexArray.h"
#include "OpenGL/OGLVertexArray.h"

namespace Forge
{
	VertexArray* VertexArray::Create()
	{
#if defined(OGL)
		return new OGLVertexArray();
#elif defined(DX)
#endif
	}
}

