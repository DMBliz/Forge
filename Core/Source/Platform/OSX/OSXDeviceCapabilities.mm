//
// Created by Дмитрий Метелица on 2/5/20.
//

#include "Platform/Api/DeviceCapabilities.h"
#import <Metal/Metal.h>

namespace Forge
{

    void DeviceCapabilities::init()
    {

    }

    GraphicsApiType DeviceCapabilities::getSupportedApi()
    {
        NSArray* devices = MTLCopyAllDevices();
        if(devices)
        {
            for (int i = 0; i < devices.count; ++i)
            {
                if(devices[i])
                {
                    //TODO: when Metal support is ready return Metal here
                    return GraphicsApiType::Vulkan;
                }
            }
        }
        //If Metal is not supported using OpenGL by default
        return GraphicsApiType::OpenGL;
    }
}