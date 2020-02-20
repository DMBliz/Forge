#pragma once
#include "Platform/Api/FileSystem.h"


namespace Forge
{
	class Win32FileSystem : public FileSystem
	{
		void GetAllFiles(std::vector<String>& files, String path);
	public:
		std::vector<String> GetFilesFromDirectory(String path) override;
	};
}
