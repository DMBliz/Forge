#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"

namespace Forge
{

	class Mesh
	{
	private:
		VertexBuffer* vb = nullptr;
		IndexBuffer* ib = nullptr;
		VertexArray* va = nullptr;
		BufferLayout layout;
	public:
		Mesh();
		~Mesh();

		void Initialize();

		void Bind();

		void SetVertexBuffer(float* vertexBuffer, uint size, BufferUsage usage);
		void SetVertexBuffer(VertexBuffer* newBuffer);

		void SetIndexBuffer(uint* indexBuffer, uint size);
		void SetIndexBuffer(IndexBuffer* newBuffer);

		uint GetIndexBufferSize() const;

		void SetBufferLayout(BufferLayout newLlayout);
		BufferLayout* GetBufferLayout();
	};

}
