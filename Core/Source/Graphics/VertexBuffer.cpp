#pragma once

#include "VertexBuffer.h"
#include "OpenGL/OGLVertexBuffer.h"

namespace Forge
{
	VertexBuffer* VertexBuffer::Create(BufferUsage usage)
	{
#if defined(OGL)
		return new OGLVertexBuffer(usage);
#elif defined(DX)
#endif
	}

	VertexBuffer* VertexBuffer::Create(const void* data, uint size, BufferUsage usage)
	{
#if defined(OGL)
		return new OGLVertexBuffer(data, size, usage);
#elif defined(DX)
#endif
	}
}
