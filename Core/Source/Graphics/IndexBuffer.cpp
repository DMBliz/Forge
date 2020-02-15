#include "IndexBuffer.h"
#include "OGL/GLIndexBuffer.h"

namespace Forge
{
	IndexBuffer* IndexBuffer::Create(uint* data, uint count)
	{
#if defined(OGL)
		return new GLIndexBuffer(data, count);
#elif defined(DX)
#endif
	}

}
