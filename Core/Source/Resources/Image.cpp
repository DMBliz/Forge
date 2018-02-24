#include "Image.h"
#include "FileSystem/File.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
#include "Resources.h"
#include "FileSystem/FileSystem.h"
#include "Core/Engine.h"

namespace Forge
{
	//TODO: write custom Vector and replace with him all std::vector usages
	Image::Image()
	{}

	Image::~Image()
	{
		_pixels.clear();
	}

	void Image::Save(String filename)
	{
		stbi_write_png(filename.CString(), _size.x, _size.y, 4, _pixels.data(), 0);
	}

	const Vector2i& Image::GetSize() const
	{
		return _size;
	}

	void Image::SetPixel(uint x, uint y, const Color& color)
	{
		if (_pixels.size() < x * y * 4)
			return;

		byte* pixel = &_pixels[(x + y * _size.x) * 4];
		
		pixel[0] = color.r;
		pixel[1] = color.g;
		pixel[2] = color.b;
		pixel[3] = color.a;
	}

	Color Image::GetPixel(uint x, uint y)
	{
		byte *pixel = &_pixels[(x + y * _size.x)];
		return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
	}

	const byte* Image::GetPixels() const
	{
		return _pixels.data();
	}

	void Image::FlipX()
	{
		if (_pixels.size() > 0)
		{
			uint rowSize = _size.x * 4;
			for(int y = 0; y < _size.y; y++)
			{
				byte* left = _pixels.begin()._Ptr + y * rowSize;
				byte* right = _pixels.begin()._Ptr + (y + 1) * rowSize - 4;

				for (int x = 0; x < _size.x / 2; x++)
				{
					SwapColors(left, right, 4);

					left += 4;
					right -= 4;
				}
			}
		}
	}

	void Image::FlipY()
	{
		if (_pixels.size() > 0)
		{
			uint rowSize = _size.x * 4;
			byte* top = _pixels.begin()._Ptr;
			byte* bottom = (_pixels.begin()._Ptr + _size.x * _size.y) - rowSize;

			for (int y = 0; y < _size.y / 2; y++)
			{
				SwapColors(top, bottom, rowSize);

				top += rowSize;
				bottom -= rowSize;
			}
		}
	}

	void Image::Load(String filename)
	{
		resourceName = filename;
		File file = engine->GetFileSystem()->ReadFile(filename);
		byte* pixels = stbi_load_from_memory(file.GetData(), file.GetSize(), &_size.x, &_size.y, &fileChannels, 4);
		_pixels.resize(_size.x * _size.x * 4);

		memcpy(_pixels.data(), pixels, _pixels.size() * sizeof(byte));
		delete[] pixels;
	}

	void Image::UnLoad()
	{

	}

	void Image::SwapColors(byte* color1, byte* color2, uint count)
	{
		byte* left = color1;
		byte* right = color2;
		byte* end = left + count;

		while(left != end)
		{
			byte temp = *left;
			*left = *right;
			*right = temp;
			left++;
			right++;
		}
	}
}
