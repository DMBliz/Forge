#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "Math/Vector3.h"

namespace Forge
{

	class Mesh
	{
	private:
		VertexBuffer* vb = nullptr;
		IndexBuffer* ib = nullptr;
		VertexArray* va = nullptr;

		std::vector<Vector3> verticies;
		std::vector<Vector2> uv;
		std::vector<Vector3> normals;
		std::vector<Vector3> tangents;
		std::vector<Vector3> bitangents;

		std::vector<std::vector<float>> custom;

		std::vector<uint> indicies;

		BufferLayout layout;

		void GenerateBuffer();
	public:
		Mesh();
		~Mesh();

		void Initialize();

		void Bind();

		void SetVertexBuffer(float* vertexBuffer, uint size, BufferUsage usage);
		void SetVertexBuffer(VertexBuffer* newBuffer);

		void SetIndexBuffer(uint* indexBuffer, uint size);
		void SetIndexBuffer(IndexBuffer* newBuffer);

		void SetVertecies(const std::vector<Vector3>& verticies);
		void SetNormals(const std::vector<Vector3>& normals);
		void SetTangents(const std::vector<Vector3>& tangents);
		void SetBitangents(const std::vector<Vector3>& bitangents);
		void SetUV(const std::vector<Vector2>& uvs);
		void SetIndexBuffer(const std::vector<uint>& indicies);

		std::vector<Vector3>& GetVertecies();
		std::vector<Vector3>& GetNormals();
		std::vector<Vector3>& GetTangents();
		std::vector<Vector3>& GetBitangents();
		std::vector<Vector2>& GetUV();
		std::vector<uint>& GetIndicies();

		uint GetIndexBufferSize() const;

		void SetBufferLayout(BufferLayout newLlayout);
		BufferLayout* GetBufferLayout();
	};

}
