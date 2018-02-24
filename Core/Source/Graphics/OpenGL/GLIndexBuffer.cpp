#include "GLIndexBuffer.h"
#include "GLCheck.h"
#include "Defines.h"

namespace Forge
{

	GLIndexBuffer::GLIndexBuffer(uint* data, uint count)
	{
		size = count;
		indicies = new uint[count];
		memcpy(indicies, data, count * sizeof(uint));
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glCheck(glDeleteBuffers(1, &bufferID));
	}

	void GLIndexBuffer::Generate()
	{
		glCheck(glGenBuffers(1, &bufferID));
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint), indicies, GL_STATIC_DRAW));
	}

	void GLIndexBuffer::Bind()
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
	}

	void GLIndexBuffer::UnBind()
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	uint GLIndexBuffer::GetCount()
	{
		return size;
	}

}
