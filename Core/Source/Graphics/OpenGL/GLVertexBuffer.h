#pragma once
#include "Graphics/VertexBuffer.h"
#include "Graphics/BufferLayout.h"

namespace Forge
{
	class GLVertexBuffer : public VertexBuffer
	{
	private:
		uint bufferID;
		uint bufferSize;
		void* bufferData = nullptr;
		BufferLayout _layout;
		uint GetOGLUsage(BufferUsage usage);
	public:
		GLVertexBuffer(BufferUsage usage);
		GLVertexBuffer(const float* data, uint size, BufferUsage usage);
		~GLVertexBuffer();

		void Generate() override;

		void SetSize(uint size) override;
		void SetLayout(const BufferLayout& layout) override;
		void SetData(const float* data, uint size) override;
		void SetDataToGPU(const float* data, uint size);

		BufferLayout& GetLayout() override { return _layout; }

		void ReleasePointer() override;

		void Bind() override;
		void UnBind() override;
	};
}
