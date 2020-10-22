#pragma once
#include "Types.h"
#include "Containers/String.h"

namespace Forge
{

	class File
	{
	private:
		byte* fileData;
		uint fileSize;
	public:
		File()
		{
			fileSize = 0;
		}

		File(byte* data, uint size)
		{
			fileSize = size;
			fileData = new byte[size];
			memcpy(fileData, data, size);
		}

		File(const char* data, uint size)
		{
			fileSize = size;
			fileData = new byte[size];
			memcpy(fileData, reinterpret_cast<const byte*>(data), size);
		}

		File(const File& newData)
		{
			delete[] fileData;
			fileSize = newData.getSize();
			memcpy(fileData, newData.getData(), fileSize);
		}

		~File()
		{
			//delete[] fileData;
		}

		String getString() const
		{
			return String(reinterpret_cast<char*>(fileData), fileSize);
		}

		File& operator=(const File& newData)
		{
			delete[] fileData;
			fileSize = newData.getSize();
			fileData = new byte[fileSize];
			memcpy(fileData, newData.getData(), fileSize);
			return *this;
		}

		File& operator=(File&& newData) noexcept
		{
			delete[] fileData;
			fileSize = newData.getSize();
			fileData = new byte[fileSize];
			memmove(fileData, newData.getData(), fileSize);
			return *this;
		}

		void setData(byte* data, uint size)
		{
			fileSize = size;

			delete[] fileData;
			fileData = new byte[size];

			memcpy(fileData, data, size);
		}

		void setData(const char* data, uint size)
		{
			fileSize = size;

			delete[] fileData;
			fileData = new byte[size];

			memcpy(fileData, reinterpret_cast<const unsigned char*>(data), size);
		}

		void resize(uint size)
		{
			byte* temp = new byte[size];
			memcpy(temp, fileData, fileSize);

			delete[] fileData;

			fileData = temp;
		}

		byte* getData() const
		{
			return fileData;
		}

		uint getSize() const
		{
			return fileSize;
		}

		std::vector<byte> toVector()
		{
			return {fileData, fileData + fileSize};
		}
	};

}
