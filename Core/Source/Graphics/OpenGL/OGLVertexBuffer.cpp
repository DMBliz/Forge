#include "OGLVertexBuffer.h"
#include "glad/glad.h"
#include "GLCheck.h"

namespace Forge
{

	OGLVertexBuffer::OGLVertexBuffer(BufferUsage usage)
	{
		_usage = usage;
	}

	OGLVertexBuffer::OGLVertexBuffer(const void* data, uint size, BufferUsage usage)
	{
		_usage = usage;
		bufferSize = size;
		bufferData = new float[size];
		memcpy(bufferData, data, size * sizeof(float));
	}

	OGLVertexBuffer::~OGLVertexBuffer()
	{
		glCheck(glDeleteBuffers(1, &bufferID));
	}

	void OGLVertexBuffer::Generate()
	{
		glCheck(glGenBuffers(1, &bufferID));

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GetOGLUsage(_usage)));

		const std::vector<BufferElement>&  elements = _layout.GetLayout();

		for (int i = 0; i < elements.size(); i++)
		{
			const BufferElement& el = elements[i];
			glCheck(glEnableVertexAttribArray(el.id));
			glCheck(glVertexAttribPointer(el.id, el.count, el.type, el.normalized, _layout.GetStride(), (const void*)el.offset));
		}
	}

	uint OGLVertexBuffer::GetOGLUsage(BufferUsage usage)
	{
		return usage == BufferUsage::DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
	}

	void OGLVertexBuffer::SetSize(uint size)
	{
		bufferSize = size;

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GetOGLUsage(_usage)));
	}

	void OGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		_layout = layout;
	}

	void OGLVertexBuffer::SetData(const void* data, uint size)
	{
		bufferSize = size;
		bufferData = new float[size];
		memcpy(bufferData, data, size * sizeof(float));
	}

	void OGLVertexBuffer::SetDataToGPU(const void* data, uint size)
	{
		SetData(data, size);
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		glCheck(glBufferData(GL_ARRAY_BUFFER, size, data, GetOGLUsage(_usage)));
	}

	void OGLVertexBuffer::ReleasePointer()
	{
		glCheck(glUnmapBuffer(bufferID));
	}

	void OGLVertexBuffer::Bind()
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	}

	void OGLVertexBuffer::UnBind()
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
