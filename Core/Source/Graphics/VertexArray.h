#pragma once
#include "Types.h"
#include <vector>
#include "VertexBuffer.h"

namespace Forge
{
	class VertexArray
	{
	protected:
		uint arrayID;
		std::vector<VertexBuffer*> buffers;
	public:

		virtual VertexBuffer* GetBuffer(uint id) = 0;
		virtual void AddBuffer(VertexBuffer* buffer) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void ReleasePointer() = 0;

		virtual void Draw(uint count) = 0;

		static VertexArray* Create();
	};
}
