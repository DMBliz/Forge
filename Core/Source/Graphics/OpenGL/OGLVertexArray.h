#pragma once
#include "Graphics/VertexArray.h"

namespace Forge
{

	class OGLVertexArray : public VertexArray
	{
	public:
		OGLVertexArray();
		~OGLVertexArray();
		
		VertexBuffer* GetBuffer(uint id) override;
		void AddBuffer(VertexBuffer* buffer) override;

		void Bind() override;
		void UnBind() override;

		void ReleasePointer() override;

		void Draw(uint count) override;
	};

}
