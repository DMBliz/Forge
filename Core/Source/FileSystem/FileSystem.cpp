#include "FileSystem.h"
#include <fstream>
#include "Defines.h"
#include <sstream>
#include "Windows/WINFileSystem.h"

namespace Forge
{

	FileSystem::FileSystem()
	{}


	FileSystem::~FileSystem()
	{}

	File FileSystem::ReadFile(const String& filename)
	{

		if (!FileExists(filename))
			LOG("File don't exist");

		std::ifstream file(filename.CString(), std::ios::binary);
		std::stringstream ss;

		ss << file.rdbuf();

		std::string tmp(ss.str());
		return File(tmp.data(), tmp.size());
	}


	void FileSystem::WriteFile(const String& filename, const String& str)
	{
	}

	bool FileSystem::FileExists(const String& filename)
	{
		std::ifstream file(filename.CString());
		bool exist = static_cast<bool>(file);
		file.close();
		return exist;
	}

	FileSystem* FileSystem::Create()
	{
		FileSystem* ret;
#if defined(_WIN32)
		ret = new WINFileSystem();
#elif defined(MACOS)
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		return ret;
	}
}
