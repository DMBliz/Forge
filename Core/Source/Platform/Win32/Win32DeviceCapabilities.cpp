//
// Created by Dmitry Metelitsa on 2/15/2020.
//

#include "Platform/Api/DeviceCapabilities.h"

namespace Forge
{
    void DeviceCapabilities::init()
    {

    }

    GraphicsApiType DeviceCapabilities::getSupportedApi()
    {
        //TODO: proper check if vulkan is supported
        //for now use OpenGL
        return GraphicsApiType::OpenGL;
    }
}