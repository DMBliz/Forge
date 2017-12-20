#pragma once
#include "Containers/String.h"
#include "File.h"

namespace Forge
{

	class FileSystem
	{
	protected:
		String appPath;

	public:
		FileSystem();
		~FileSystem();
		
		static File ReadFile(const String& filename);
		static void WriteFile(const String& filename, const String& str);
		static bool FileExists(const String& filename);
	};

}
