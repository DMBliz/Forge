#include "FileSystem.h"
#include <fstream>
#include "Defines.h"
#include <sstream>

namespace Forge
{

	FileSystem::FileSystem()
	{}


	FileSystem::~FileSystem()
	{}

	File FileSystem::readFile(const String& filename)
	{
		if (!fileExists(filename))
			LOG("File don't exist " + filename);

		std::ifstream file(filename.cString(), std::ios::binary);
		std::stringstream ss;

		ss << file.rdbuf();

		file.close();

		std::string tmp(ss.str());
		return File(tmp.data(), tmp.size());
	}


	void FileSystem::writeFile(const String& filename, const String& str)
	{
        std::ofstream file(filename.cString(), std::ios::binary);
        file.open(filename.cString());
        
        file << str.cString();
        
        file.close();
	}

	bool FileSystem::fileExists(const String& filename)
	{
		std::ifstream file(filename.cString());
        
		bool exist = static_cast<bool>(file);
		file.close();
		return exist;
	}
}
