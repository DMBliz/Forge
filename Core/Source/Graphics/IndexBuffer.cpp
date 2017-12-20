#include "IndexBuffer.h"
#include "OpenGL/OGLIndexBuffer.h"

namespace Forge
{
	IndexBuffer* IndexBuffer::Create(uint* data, uint count)
	{
#if defined(OGL)
		return new OGLIndexBuffer(data, count);
#elif defined(DX)
#endif
	}

}
