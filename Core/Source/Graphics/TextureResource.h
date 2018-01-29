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

	enum class TextureFormat
	{
		None,
		RGB,
		RGBA
	};

	struct TextureParametrs
	{
		TextureFilter filter;
		TextureWrap wrap;
		TextureFormat format;


		TextureParametrs()
			: filter(TextureFilter::Linear), wrap(TextureWrap::Repeat), format(TextureFormat::RGBA)
		{}

		TextureParametrs(TextureFilter filter, TextureWrap wrap, TextureFormat format)
			: filter(filter), wrap(wrap), format(format)
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
