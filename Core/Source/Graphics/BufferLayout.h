#pragma once
#include "Containers/String.h"
#include "Types.h"

namespace Forge
{
	enum class BufferElementType
	{
		Custom,
		Position,
		UV,
		Normal,
		Tangent,
		Bitangent

	};
	struct BufferElement
	{
		String name;
		uint id;
		uint type;//element type
		uint size;//size of 1 element in bytes
		uint count;//count of numbers
		uint offset;
		BufferElementType elementType;
		uint customID;
		bool normalized;
	};

	class BufferLayout
	{
	private:
		uint layoutSize;
		std::vector<BufferElement> layout;

		void Add(const String& name, uint id, uint type, uint size, uint count, 
				 BufferElementType elemType = BufferElementType::Custom, uint customID = 0, bool normalized = false);
	public:

		BufferLayout();

		template<typename T>
		void Add(const String& name, uint id, uint count,
				 BufferElementType elemType = BufferElementType::Custom, uint customID = 0, bool normalized = false);

		template<typename T>
		void Add(const String& name, uint id, 
				 BufferElementType elemType = BufferElementType::Custom, uint customID = 0, bool normalized = false);

		BufferLayout& operator=(const BufferLayout& right);

		const std::vector<BufferElement>& GetLayout() const;
		inline uint GetStride() const { return layoutSize; }

	};

	
}
