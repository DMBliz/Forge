#pragma once

#include "VertexBuffer.h"
#include "OpenGL/GLVertexBuffer.h"

namespace Forge
{
	VertexBuffer* VertexBuffer::Create(BufferUsage usage)
	{
#if defined(OGL)
		return new GLVertexBuffer(usage);
#elif defined(DX)
#endif
	}

	VertexBuffer* VertexBuffer::Create(const float* data, uint size, BufferUsage usage)
	{
#if defined(OGL)
		return new GLVertexBuffer(data, size, usage);
#elif defined(DX)
#endif
	}
}
