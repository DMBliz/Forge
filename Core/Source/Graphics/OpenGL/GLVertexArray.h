#pragma once
#include "Graphics/VertexArray.h"

namespace Forge
{

	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		~GLVertexArray();
		
		VertexBuffer* GetBuffer(uint id) override;
		void AddBuffer(VertexBuffer* buffer) override;

		void Bind() override;
		void UnBind() override;

		void ReleasePointer() override;

		void Draw(uint count) override;
	};

}
