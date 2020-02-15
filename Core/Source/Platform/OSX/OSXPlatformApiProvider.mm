//
// Created by Дмитрий Метелица on 2019-10-24.
//

#include "Platform/Api/PlatformApiProvider.h"
#include "OSXFileSystem.h"
#include "OSXInput.h"
#include "Platform/Api/DeviceCapabilities.h"
#import "OSXContextApi.h"

namespace Forge
{
    void PlatformApiProvider::init()
    {
        addApi("WindowSystem", new WindowSystem());
        addApi("ContextApi", new OSXContextApi());
        addApi("InputSystem", new OSXInput());
        addApi("FileSystem", new OSXFileSystem());
        addApi("DeviceCapabilities", new DeviceCapabilities());
    }
}