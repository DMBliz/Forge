#include "GLVertexArray.h"
#include "glad/glad.h"
#include "GLCheck.h"
#include "Containers/String.h"
#include "Defines.h"

namespace Forge
{

	GLVertexArray::GLVertexArray()
	{
		glCheck(glGenVertexArrays(1, &arrayID));
	}

	GLVertexArray::~GLVertexArray()
	{
		glCheck(glDeleteVertexArrays(1, &arrayID));
	}

	VertexBuffer* GLVertexArray::GetBuffer(uint id)
	{
		return (id < buffers.size()) ? buffers[id] : nullptr;
	}

	void GLVertexArray::AddBuffer(VertexBuffer* buffer)
	{
		buffers.push_back(buffer);
	}

	void GLVertexArray::Bind()
	{
		glCheck(glBindVertexArray(arrayID));
	}

	void GLVertexArray::UnBind()
	{
		glCheck(glBindVertexArray(0));
	}

	void GLVertexArray::Draw(uint count)
	{
		glCheck(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void GLVertexArray::ReleasePointer()
	{
		glDeleteVertexArrays(1, &arrayID);
	}
}
