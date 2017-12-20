#include "BufferLayout.h"
#include "glad/glad.h"
#include "Defines.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Forge
{
	void BufferLayout::Add(const String& name, uint id, uint type, uint size, uint count, bool normalized)
	{
		layout.push_back({ name, id, type, size, count, layoutSize, normalized });
		layoutSize += size * count;
	}

	BufferLayout::BufferLayout()
		: layoutSize(0)
	{}

	template<typename T>
	void BufferLayout::Add(const String& name, uint id, uint count, bool normalized)
	{
		LOG("Unsupported type");
	}

	template <>
	void BufferLayout::Add<float>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), count, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<uint>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<byte>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector2>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 2, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector3>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 3, normalized);
#elif defined(DX)
#endif
	}

	template <>
	void BufferLayout::Add<Vector4>(const String& name, uint id, uint count, bool normalized)
	{
#if defined(OGL)
		Add(name, id, GL_FLOAT, sizeof(float), 4, normalized);
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
