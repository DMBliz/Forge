#pragma once
#include "Containers/String.h"
#include "File.h"
#include "Api.h"

namespace Forge
{

	class FileSystem : public Api
	{
	protected:
		String appPath;

	public:
		FileSystem();
		~FileSystem();
		
		virtual File ReadFile(const String& filename);
		virtual void WriteFile(const String& filename, const String& str);
		virtual bool FileExists(const String& filename);

		virtual std::vector<String> GetFilesFromDirectory(String path) = 0;
        

		static FileSystem* Create();
	};

}
