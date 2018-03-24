#pragma once
#include "Types.h"
#include "Containers/String.h"
#include "Math/Mathf.h"

namespace Forge
{
    class Texture2D;

    enum class UniformDataType
	{
		FLOAT,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		COLOR,
		INTEGER,
		VECTOR2I,
		UNSIGNED_INTEGER,
		MATRIX3,
		MATRIX4,
		SAMPLER2D
	};

	struct UniformDescription
	{
		String name;
		int location;
		UniformDataType type;
		uint _count;
		void* data = nullptr;
		bool locationResolved = false;

        void SetName(const String& name);

        template<typename  T>
        void SetValue(uint count, T* value);

        template<typename  T>
        void SetValue(T value);

        void SetTexture(const Texture2D& texture);
        void SetTexture(uint textureID);
        void SetValueTextureSlot(uint slot);

		~UniformDescription()
		{
			DeleteData();
		}

	private:
		void DeleteData();
	};


}
