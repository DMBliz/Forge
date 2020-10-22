//
// Created by Dmitry Metelitsa on 2019-07-28.
//

#pragma once
#include "Platform/Api/FileSystem.h"

namespace Forge
{

    class MacOSFileSystem : public FileSystem
    {
    public:

        std::vector<String> getFilesFromDirectory(String path) override;
        
        
    };

}
