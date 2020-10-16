//
// Created by Dmitry Metelitsa on 2/5/20.
//

#include "Platform/Api/DeviceCapabilities.h"
#import <Metal/Metal.h>
#import <Cocoa/Cocoa.h>

namespace Forge
{

    void DeviceCapabilities::init()
    {
        NSRect screenRect = [[NSScreen mainScreen] frame];
        screenSize.x = static_cast<int>(screenRect.size.width);
        screenSize.y = static_cast<int>(screenRect.size.height);
//        [[NSScreen mainScreen] backingScaleFactor]
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

    const Vector2i& DeviceCapabilities::getScreenSize() const
    {
        return screenSize;
    }
}