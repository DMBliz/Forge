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
		
		virtual File readFile(const String& filename);
		virtual void writeFile(const String& filename, const String& str);
		virtual bool fileExists(const String& filename);

		virtual std::vector<String> getFilesFromDirectory(String path) = 0;
        

		static FileSystem* Create();
	};

}
