#pragma once
#include "Types.h"
#include "Containers/String.h"
#include "Resources/Resource.h"

namespace Forge
{

	enum class TextureWrap
	{
		None,
		Repeat,
		Mirrored_Repeat,
		Clamp_to_Edge,
		Clamp_to_border
	};

	enum class TextureFilter
	{
		None,
		Linear,
		Nearest
	};

	enum class TextureInternalFormat
	{
		None,
		RGB,
		RGBA,
		DepthStencil
	};

	enum class TextureFormat
	{
		None,
		RGB,
		RGBA,
		DepthStencil
	};

	enum class TextureDataType
	{
		Byte,
		UnsignedInt,
		UnsignedInt_24_8
	};

	struct TextureParametrs
	{
		TextureFilter filter;
		TextureWrap wrap;
		TextureInternalFormat internalFormat;
		TextureFormat format;
		TextureDataType dataType;

		TextureParametrs(TextureFilter filter = TextureFilter::Nearest, TextureWrap wrap = TextureWrap::Repeat,
						 TextureInternalFormat internalFormat = TextureInternalFormat::RGBA,
						 TextureFormat format = TextureFormat::RGBA, TextureDataType dataType = TextureDataType::Byte)
			: filter(filter), wrap(wrap), internalFormat(internalFormat), format(format), dataType(dataType)
		{}
	};

	class TextureResource
	{
	protected:
		TextureParametrs parametrs;
		uint textureID;
	public:
		virtual ~TextureResource() = default;

		uint GetID() const { return textureID; }

		virtual void Bind(uint slot = 0) const = 0;
		virtual void UnBind(uint slot = 0) const = 0;
		virtual void SetParameters(TextureParametrs params) = 0;
	};
}
