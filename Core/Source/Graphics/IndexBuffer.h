#pragma once
#include "Types.h"

namespace Forge
{
	class IndexBuffer
	{
	protected:
		uint* indicies;
		uint size;
	public:

		virtual void Generate() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint GetCount() = 0;

		static IndexBuffer* Create(uint* data, uint count);
	};

}
