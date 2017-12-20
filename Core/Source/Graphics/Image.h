#pragma once
#include "Types.h"
#include "Math/Vector2i.h"
#include "Math/Color.h"

namespace Forge
{
	class File;
	//TODO: optimize channels
	//TODO: make own image loader
	class Image
	{
	private:
		byte* _pixels;
		Vector2i _size;
		int fileChannels;

		void SwapColors(byte* color1, byte* color2, uint count, int inter);
	public:
		Image();
		Image(const File& file);
		Image(const byte* pixels, const Vector2i& size);
		Image(const Vector2i& size, const Color& color = Color(0, 0, 0));

		~Image();

		void Create(const Vector2i& size, const Color& color = Color(0, 0, 0));
		void Create(const byte* pixels, const Vector2i& size);
		void Create(const File& file);

		void SetPixel(uint x, uint y, const Color& color);
		Color GetPixel(uint x, uint y);

		const Vector2i& GetSize() const;
		const byte* GetPixels() const;

		void FlipX();
		void FlipY();
	};

}
