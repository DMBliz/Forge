#pragma once
#include "Containers/String.h"
#include "Types.h"

namespace Forge
{
	//TODO: rework buffers pipline buffer layout has all data for each layout
	struct BufferElement
	{
		String name;
		uint id;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

	class BufferLayout
	{
	private:
		uint layoutSize;
		std::vector<BufferElement> layout;

		void Add(const String& name, uint id, uint type, uint size, uint count, bool normalized);
	public:

		BufferLayout();

		template<typename T>
		void Add(const String& name, uint id, uint count, bool normalized);

		BufferLayout& operator=(const BufferLayout& right);

		const std::vector<BufferElement>& GetLayout() const;
		inline uint GetStride() const { return layoutSize; }

	};
}
