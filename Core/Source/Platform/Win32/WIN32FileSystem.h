#pragma once
#include "Platform/Api/FileSystem.h"


namespace Forge
{
	class Win32FileSystem : public FileSystem
	{
		void getAllFiles(std::vector<String>& files, String path);
	public:
		std::vector<String> getFilesFromDirectory(String path) override;
	};
}
