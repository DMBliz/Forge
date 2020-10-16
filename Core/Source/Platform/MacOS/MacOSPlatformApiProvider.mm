//
// Created by Dmitry Metelitsa on 2019-10-24.
//

#include "Platform/Api/WindowSystem.h"
#include "Platform/Api/ContextApi.h"
#include "Platform/Api/PlatformApiProvider.h"
#include "MacOSFileSystem.h"
#include "Platform/Api/DeviceCapabilities.h"

namespace Forge
{
    void PlatformApiProvider::init()
    {
        addApi("WindowSystem", new WindowSystem());
        addApi("ContextApi", new ContextApi());
        addApi("FileSystem", new MacOSFileSystem());
        addApi("DeviceCapabilities", new DeviceCapabilities());

        for(auto it = apis.begin(); it != apis.end(); it++)
        {
            it->second->init();
        }
    }
}