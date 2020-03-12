//
// Created by Дмитрий Метелица on 2019-10-24.
//

#include <Platform/Api/WindowSystem.h>
#include "Platform/Api/PlatformApiProvider.h"
#include "OSXFileSystem.h"
#include "Platform/Api/DeviceCapabilities.h"
#include "OSXContextApi.h"

namespace Forge
{
    void PlatformApiProvider::init()
    {
        addApi("WindowSystem", new WindowSystem());
        addApi("ContextApi", new OSXContextApi());
        addApi("FileSystem", new OSXFileSystem());
        addApi("DeviceCapabilities", new DeviceCapabilities());

        for(auto it = apis.begin(); it != apis.end(); it++)
        {
            it->second->init();
        }
    }
}