#include "GLVertexBuffer.h"
#include "glad/glad.h"
#include "GLCheck.h"

namespace Forge
{

	GLVertexBuffer::GLVertexBuffer(BufferUsage usage)
	{
		_usage = usage;
	}

	GLVertexBuffer::GLVertexBuffer(const float* data, uint size, BufferUsage usage)
	{
		_usage = usage;
		bufferSize = size;
		bufferData = new float[size];
		memcpy(bufferData, data, size * sizeof(float));
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glCheck(glDeleteBuffers(1, &bufferID));
	}

	void GLVertexBuffer::Generate()
	{
		glCheck(glGenBuffers(1, &bufferID));

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(float), bufferData, GetOGLUsage(_usage)));

		const std::vector<BufferElement>&  elements = _layout.GetLayout();

		for (int i = 0; i < elements.size(); i++)
		{
			const BufferElement& el = elements[i];
			glCheck(glEnableVertexAttribArray(el.id));
			glCheck(glVertexAttribPointer(el.id, el.count, el.type, el.normalized, _layout.GetStride(), (const void*)el.offset));
		}
	}

	uint GLVertexBuffer::GetOGLUsage(BufferUsage usage)
	{
		return usage == BufferUsage::DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
	}

	void GLVertexBuffer::SetSize(uint size)
	{
		bufferSize = size;

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GetOGLUsage(_usage)));
	}

	void GLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		_layout = layout;
	}

	void GLVertexBuffer::SetData(const float* data, uint size)
	{
		bufferSize = size;
		bufferData = new float[size];
		memcpy(bufferData, data, size * sizeof(float));
	}

	void GLVertexBuffer::SetDataToGPU(const float* data, uint size)
	{
		SetData(data, size);
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, size, data, GetOGLUsage(_usage)));
	}

	void GLVertexBuffer::ReleasePointer()
	{
		glCheck(glUnmapBuffer(bufferID));
	}

	void GLVertexBuffer::Bind()
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	}

	void GLVertexBuffer::UnBind()
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
