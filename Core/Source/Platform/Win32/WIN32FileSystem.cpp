#include "WIN32FileSystem.h"
#include "windows.h"

namespace Forge
{
	void WINFileSystem::GetAllFiles(std::vector<String>& files, String path)
	{
		String fpath = path + "*";
		WIN32_FIND_DATA data;
		HANDLE handle = FindFirstFile(fpath.CString(), &data);

		if (handle != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (data.cFileName[0] != '.')
				{
					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						GetAllFiles(files, path + data.cFileName + "/");
					else
						files.push_back(path + data.cFileName);
				}

			} while (FindNextFile(handle, &data));
			FindClose(handle);
		}
	}

	std::vector<String> WINFileSystem::GetFilesFromDirectory(String path)
	{
		std::vector<String> files;
		
		GetAllFiles(files, path);

		return files;
	}
}
