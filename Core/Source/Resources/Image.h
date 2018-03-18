#pragma once
#include "Types.h"
#include "Math/Vector2i.h"
#include "Math/Color.h"
#include "Resource.h"

namespace Forge
{
	class File;
	//TODO: optimize channels
	//TODO: make own image loader
	//Representing image on CPU memory
	class Image : public Resource
	{
	private:
		std::vector<byte> _pixels;
		Vector2i _size;
		int fileChannels;

		void SwapColors(byte* color1, byte* color2, uint count);
	public:
		Image();
		~Image();

		void Save(String filename);

		void SetPixel(uint x, uint y, const Color& color);
		Color GetPixel(uint x, uint y);

		const Vector2i& GetSize() const;
		const byte* GetPixels() const;

		void FlipX();
		void FlipY();

		void Load(const String& filename) override;
		void UnLoad() override;
	};

}
