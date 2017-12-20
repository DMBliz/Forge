#include "Image.h"
#include "FileSystem/File.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace Forge
{

	Image::Image()
	{}

	Image::Image(const File& file)
	{
		_pixels = stbi_load_from_memory(file.GetData(), file.GetSize(), &_size.x, &_size.y, &fileChannels, 4);
	}

	Image::Image(const byte* pixels, const Vector2i& size)
	{
		_size = size;

		_pixels = new byte[size.x * size.y * 4];

		memcpy(_pixels, pixels, size.x * size.y * 4);
	}

	Image::Image(const Vector2i& size, const Color& color)
	{
		_size = size;

		_pixels = new byte[size.x * size.y * 4];

		byte *current = &_pixels[0];
		byte *end = &_pixels[size.x * size.y * 4];

		while (current < end)
		{
			*current = color.r;
			current++;
			*current = color.b;
			current++;
			*current = color.g;
			current++;
			*current = color.a;
			current++;
		}
	}

	Image::~Image()
	{
		delete[] _pixels;
	}

	void Image::Create(const Vector2i& size, const Color& color)
	{
		_size = size;

		delete[] _pixels;

		_pixels = new byte[size.x * size.y];

		byte *current = &_pixels[0];
		byte *end = &_pixels[size.x * size.y];

		while (current < end)
		{
			*current = color.r;
			current++;
			*current = color.b;
			current++;
			*current = color.g;
			current++;
			*current = color.a;
			current++;
		}
	}

	void Image::Create(const byte* pixels, const Vector2i& size)
	{
		_size = size;

		delete[] _pixels;

		_pixels = new byte[size.x * size.y];

		memcpy(_pixels, pixels, size.x * size.y);
	}

	void Image::Create(const File& file)
	{
		delete[] _pixels;
		_size.Set(0, 0);

		_pixels = stbi_load_from_memory(file.GetData(), file.GetSize(), &_size.x, &_size.y, &fileChannels, 4);
		
	}

	const Vector2i& Image::GetSize() const
	{
		return _size;
	}

	void Image::SetPixel(uint x, uint y, const Color& color)
	{
		byte *pixel = &_pixels[(x + y * _size.x) * 4];
		*pixel = color.r;
		pixel++;
		*pixel = color.b;
		pixel++;
		*pixel = color.g;
		pixel++;
		*pixel = color.a;
	}

	Color Image::GetPixel(uint x, uint y)
	{
		byte *pixel = &_pixels[(x + y * _size.x) * 4];
		return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
	}

	const byte* Image::GetPixels() const
	{
		return _pixels;
	}

	void Image::FlipX()
	{
		if (_pixels)
		{
			uint rowSize = _size.x * 4;
			for(int y = 0; y < _size.y; y++)
			{
				byte* left = _pixels + y * rowSize;
				byte* right = _pixels + (y + 1) * rowSize - 4;

				for (int x = 0; x < _size.x / 2; x++)
				{
					SwapColors(left, right, 4, x);

					left += 4;
					right -= 4;
				}
			}
		}
	}

	void Image::FlipY()
	{
		if (_pixels)
		{
			uint rowSize = _size.x * 4;
			byte* top = _pixels;
			byte* bottom = (_pixels + _size.x * _size.y * 4) - rowSize;

			for (int y = 0; y < _size.y / 2; y++)
			{
				SwapColors(top, bottom, rowSize, y);

				top += rowSize;
				bottom -= rowSize;
			}
		}
	}

	void Image::SwapColors(byte* color1, byte* color2, uint count, int inter)
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
