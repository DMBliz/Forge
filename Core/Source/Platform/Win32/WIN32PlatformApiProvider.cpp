//
// Created by Дмитрий Метелица on 2019-10-24.
//

#include "WIN32App.h"
#include "WIN32Input.h
#include "WIN32FileSystem.h"

namespace Forge
{
    void PlatformApiProvider::init()
    {
        addApi("WindowSystem", new WIN32WindowSystem());
        addApi("InputSystem", new WIN32Input());
        addApi("FileSystem", new WIN32FileSystem());
    }
}