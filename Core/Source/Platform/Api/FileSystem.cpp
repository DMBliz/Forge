#include "FileSystem.h"
#include <fstream>
#include "Defines.h"
#include <sstream>
#if defined(WIN32)
#include "Win32/WIN32FileSystem.h"
#elif defined(OSX)
#include "Platform/OSX/OSXFileSystem.h"
#endif


namespace Forge
{

	FileSystem::FileSystem()
	{}


	FileSystem::~FileSystem()
	{}

	File FileSystem::ReadFile(const String& filename)
	{
		if (!FileExists(filename))
			LOG("File don't exist " + filename);

		std::ifstream file(filename.CString(), std::ios::binary);
		std::stringstream ss;

		ss << file.rdbuf();

		file.close();

		std::string tmp(ss.str());
		return File(tmp.data(), tmp.size());
	}


	void FileSystem::WriteFile(const String& filename, const String& str)
	{
        std::ofstream file(filename.CString(), std::ios::binary);
        file.open(filename.CString());
        
        file << str.CString();
        
        file.close();
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
#if defined(WIN32)
		ret = new WIN32FileSystem();
#elif defined(OSX)
        ret = new OSXFileSystem();
#elif defined(LINUX)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		return ret;
	}
}
