#include "OGLIndexBuffer.h"
#include "GLCheck.h"
#include "Defines.h"

namespace Forge
{

	OGLIndexBuffer::OGLIndexBuffer(uint* data, uint count)
	{
		size = count;
		indicies = new uint[count];
		memcpy(indicies, data, count * sizeof(uint));
	}

	OGLIndexBuffer::~OGLIndexBuffer()
	{
		glCheck(glDeleteBuffers(1, &bufferID));
	}

	void OGLIndexBuffer::Generate()
	{
		glCheck(glGenBuffers(1, &bufferID));
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint16), indicies, GL_STATIC_DRAW));
	}

	void OGLIndexBuffer::Bind()
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
	}

	void OGLIndexBuffer::UnBind()
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	uint OGLIndexBuffer::GetCount()
	{
		return size;
	}

}
