//
// Created by Дмитрий Метелица on 2019-10-24.
//
#include "Platform/Api/PlatformApiProvider.h"
#include "Win32Input.h"
#include "Win32FileSystem.h"
#include "Win32ContextApi.h"

namespace Forge
{
    void PlatformApiProvider::init()
    {
        addApi("ContextApi", new Win32ContextApi());
        addApi("InputSystem", new Win32Input());
        addApi("FileSystem", new Win32FileSystem());
    }
}