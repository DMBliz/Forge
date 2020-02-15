#include "Mesh.h"
#include "Math/Vector2.h"

namespace Forge
{
	void Mesh::GenerateBuffer()
	{
		std::vector<float> data;

		if(verticies.size() <= 0)
			return;

		for (int i = 0; i < verticies.size(); i++)
		{
			for (int j = 0; j < layout.GetLayout().size(); j++)
			{
				if(layout.GetLayout()[j].elementType == BufferElementType::Position)
				{
					data.push_back(verticies[i].x);
					data.push_back(verticies[i].y);
					data.push_back(verticies[i].z);
				}

				if (layout.GetLayout()[j].elementType == BufferElementType::UV)
				{
					if (uv.size() > i)
					{
						data.push_back(uv[i].x);
						data.push_back(uv[i].y);
					}
					else
					{
						data.push_back(0);
						data.push_back(0);
					}
				}

				if (layout.GetLayout()[j].elementType == BufferElementType::Normal)
				{
					if (normals.size() > i)
					{
						data.push_back(normals[i].x);
						data.push_back(normals[i].y);
						data.push_back(normals[i].z);
					}
					else
					{
						data.push_back(0);
						data.push_back(0);
						data.push_back(0);
					}
				}

				if (layout.GetLayout()[j].elementType == BufferElementType::Tangent)
				{
					if (tangents.size() > i)
					{
						data.push_back(tangents[i].x);
						data.push_back(tangents[i].y);
						data.push_back(tangents[i].z);
					}
					else
					{
						data.push_back(0);
						data.push_back(0);
						data.push_back(0);
					}
				}

				if (layout.GetLayout()[j].elementType == BufferElementType::Bitangent && bitangents.size() < i)
				{
					if (bitangents.size() > i)
					{
						data.push_back(bitangents[i].x);
						data.push_back(bitangents[i].y);
						data.push_back(bitangents[i].z);
					}
					else
					{
						data.push_back(0);
						data.push_back(0);
						data.push_back(0);
					}
				}

				int custID = layout.GetLayout()[j].customID;

				if(layout.GetLayout()[j].elementType == BufferElementType::Custom)
				{
					if(custom.size() > custID && custom[custID].size() > 0)
					{
						for (int k = 0; k < layout.GetLayout()[j].count; k++)
						{
							data.push_back(custom[custID][k]);
						}
					}
					else
					{
						for (int k = 0; k < layout.GetLayout()[j].count; k++)
						{
							data.push_back(0);
						}
					}
				}
			}
		}

		vb = VertexBuffer::Create(data.data(), data.size());
		ib = IndexBuffer::Create(indicies.data(), indicies.size());
	}

	Mesh::Mesh()
	{}

	Mesh::~Mesh()
	{}

	void Mesh::Initialize()
	{
		GenerateBuffer();
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

	void Mesh::SetVertecies(const std::vector<Vector3>& verticies)
	{
		this->verticies = verticies;
	}

	void Mesh::SetNormals(const std::vector<Vector3>& normals)
	{
		this->normals = normals;
	}

	void Mesh::SetTangents(const std::vector<Vector3>& tangents)
	{
		this->tangents = tangents;
	}

	void Mesh::SetBitangents(const std::vector<Vector3>& bitangents)
	{
		this->bitangents = bitangents;
	}

	void Mesh::SetUV(const std::vector<Vector2>& uvs)
	{
		this->uv = uvs;
	}

	void Mesh::SetIndexBuffer(const std::vector<uint>& indicies)
	{
		this->indicies = indicies;
	}

	std::vector<Vector3>& Mesh::GetVertecies()
	{
		return verticies;
	}

	std::vector<Vector3>& Mesh::GetNormals()
	{
		return normals;
	}

	std::vector<Vector3>& Mesh::GetTangents()
	{
		return tangents;
	}

	std::vector<Vector3>& Mesh::GetBitangents()
	{
		return bitangents;
	}

	std::vector<Vector2>& Mesh::GetUV()
	{
		return uv;
	}

	std::vector<uint>& Mesh::GetIndicies()
	{
		return indicies;
	}

	uint Mesh::GetIndexBufferSize() const
	{
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
