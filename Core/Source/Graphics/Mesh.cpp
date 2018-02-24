#include "Mesh.h"

namespace Forge
{

	Mesh::Mesh()
	{}

	Mesh::~Mesh()
	{}

	void Mesh::Initialize()
	{
		va = VertexArray::Create();
		va->Bind();

		vb->SetLayout(layout);

		vb->Generate();
		ib->Generate();

		va->UnBind();
		vb->UnBind();
		ib->UnBind();

		va->AddBuffer(vb);
	}

	void Mesh::Bind()
	{
		va->Bind();
		
	}

	void Mesh::SetVertexBuffer(float* vertexBuffer, uint size, BufferUsage usage)
	{
		if (vb != nullptr)
			delete vb;
		vb = VertexBuffer::Create(vertexBuffer, size, usage);
	}

	void Mesh::SetVertexBuffer(VertexBuffer* newBuffer)
	{
		if (vb != nullptr)
			delete vb;
		vb = newBuffer;
	}

	void Mesh::SetIndexBuffer(uint* indexBuffer, uint size)
	{
		if (ib != nullptr)
			delete ib;
		ib = IndexBuffer::Create(indexBuffer, size);
	}

	void Mesh::SetIndexBuffer(IndexBuffer* newBuffer)
	{
		if (ib != nullptr)
			delete ib;
		ib = newBuffer;
	}

	uint Mesh::GetIndexBufferSize() const
	{
		if (ib == nullptr)
			return 0;
		return ib->GetCount();
	}

	void Mesh::SetBufferLayout(BufferLayout newLayout)
	{
		layout = newLayout;
	}

	BufferLayout* Mesh::GetBufferLayout()
	{
		return &layout;
	}
}
