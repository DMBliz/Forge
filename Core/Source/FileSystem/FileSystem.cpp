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

	File FileSystem::ReadFile(const String& filename)
	{
		/*std::ifstream file(filename.CString());
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> buffer(size);
		String res;
		res.Resize(size);
		if (!file.read(res.CString(), size))
		{
			LOG("File read error");
		}*/

		if (!FileExists(filename))
			LOG("File don't exist");

		std::ifstream file(filename.CString(), std::ios::binary);
		std::stringstream ss;

		ss << file.rdbuf();

		std::string tmp(ss.str());
		/*
		std::ifstream file(filename.CString(), std::ios::binary);
		String res;

		std::string temp{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
		res = temp.c_str();*/

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
}
