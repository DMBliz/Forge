#pragma once
#include "Graphics/VertexBuffer.h"
#include "Graphics/BufferLayout.h"

namespace Forge
{
	class OGLVertexBuffer : public VertexBuffer
	{
	private:
		uint bufferID;
		uint bufferSize;
		void* bufferData = nullptr;
		BufferLayout _layout;
		uint GetOGLUsage(BufferUsage usage);
	public:
		OGLVertexBuffer(BufferUsage usage);
		OGLVertexBuffer(const void* data, uint size, BufferUsage usage);
		~OGLVertexBuffer();

		void Generate() override;

		void SetSize(uint size) override;
		void SetLayout(const BufferLayout& layout) override;
		void SetData(const void* data, uint size) override;
		void SetDataToGPU(const void* data, uint size);

		BufferLayout& GetLayout() override { return _layout; }

		void ReleasePointer() override;

		void Bind() override;
		void UnBind() override;
	};
}
