//
// Created by Дмитрий Метелица on 2019-07-28.
//

#pragma once
#include "Platform/Api/FileSystem.h"

namespace Forge
{

    class OSXFileSystem : public FileSystem
    {
    public:

        std::vector<String> GetFilesFromDirectory(String path) override;
        
        
    };

}
