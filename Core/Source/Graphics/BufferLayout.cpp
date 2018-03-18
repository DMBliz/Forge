#include "BufferLayout.h"
#include "glad/glad.h"
#include "Defines.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Forge
{
	void BufferLayout::Add(const String& name, uint id, uint type, uint size, uint count, 
						   BufferElementType elemType, uint customID, bool normalized)
	{
		layout.push_back({ name, id, type, size, count, layoutSize, elemType, customID, normalized });
		layoutSize += size * count;
	}

	template <typename T>
	void BufferLayout::Add(const String& name, uint id, uint count, BufferElementType elemType, uint customID, bool normalized)
	{
		LOG("Unsupported type");
	}

	template <typename T>
	void BufferLayout::Add(const String& name, uint id, BufferElementType elemType, uint customID, bool normalized)
	{
		LOG("Unsupported type");
	}

	BufferLayout::BufferLayout()
		: layoutSize(0)
	{}

	template <>
	void BufferLayout::Add<float>(const String& name, uint id, uint count,
								  BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), count, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<uint>(const String& name, uint id, uint count,
								 BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_UNSIGNED_INT, sizeof(uint), count, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<byte>(const String& name, uint id, uint count,
								 BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_UNSIGNED_BYTE, sizeof(byte), count, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector2>(const String& name, uint id,
									BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 2, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector3>(const String& name, uint id,
									BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 3, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector4>(const String& name, uint id,
									BufferElementType elemType, uint customID, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 4, elemType, customID, normalized);
#elif defined(DX)
#endif
	}

	BufferLayout& BufferLayout::operator=(const BufferLayout& right)
	{
		layoutSize = right.layoutSize;
		layout = right.layout;
		return *this;
	}

	const std::vector<BufferElement>& BufferLayout::GetLayout() const
	{
		return layout;
	}
}
