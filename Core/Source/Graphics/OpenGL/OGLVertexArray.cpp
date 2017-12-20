#include "OGLVertexArray.h"
#include "glad/glad.h"
#include "GLCheck.h"
#include "Containers/String.h"
#include "Defines.h"

namespace Forge
{

	OGLVertexArray::OGLVertexArray()
	{
		glCheck(glGenVertexArrays(1, &arrayID));
	}

	OGLVertexArray::~OGLVertexArray()
	{
		glCheck(glDeleteVertexArrays(1, &arrayID));
	}

	VertexBuffer* OGLVertexArray::GetBuffer(uint id)
	{
		return (id < buffers.size()) ? buffers[id] : nullptr;
	}

	void OGLVertexArray::AddBuffer(VertexBuffer* buffer)
	{
		buffers.push_back(buffer);
	}

	void OGLVertexArray::Bind()
	{
		glCheck(glBindVertexArray(arrayID));
	}

	void OGLVertexArray::UnBind()
	{
		glCheck(glBindVertexArray(0));
	}

	void OGLVertexArray::Draw(uint count)
	{
		glCheck(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void OGLVertexArray::ReleasePointer()
	{
		glDeleteVertexArrays(1, &arrayID);
	}
}
