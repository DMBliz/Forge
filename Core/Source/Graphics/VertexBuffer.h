#pragma once
#include "Types.h"

namespace Forge
{
	class BufferLayout;

	enum class BufferUsage
	{
		STATIC, DYNAMIC
	};

	class VertexBuffer
	{
	protected:
		BufferUsage _usage;
	public:

		virtual void SetSize(uint size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const float* data, uint size) = 0;

		virtual void ReleasePointer() = 0;
		virtual void Generate() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual BufferLayout& GetLayout() = 0;

		static VertexBuffer* Create(BufferUsage usage = BufferUsage::STATIC);
		static VertexBuffer* Create(const float* data, uint size, BufferUsage usage = BufferUsage::STATIC);
		
	};
}
