//
// Created by Dmitry Metelitsa on 2/11/20.
//

#include <Platform/Api/DeviceCapabilities.h>
#include "Platform/Api/ContextApi.h"
#if defined(OGL)
#include "Platform/MacOS/Context/OGL/OGLMacOSContext.h"
#endif
#if defined(VK)
//TODO: include vulkan context
#endif

namespace Forge
{
    Context* ContextApi::createContext(GraphicsApiType gapi)
    {
        Context* ret;
        switch(gapi)
        {
            case GraphicsApiType::Vulkan:
#if defined(VK)

#endif
    //For even if Vulkan is supported we use OpenGL because we don't have Metal Render
            case GraphicsApiType::OpenGL:
#if defined(OGL)
                ret = new OGLMacOSContext();
#endif
                break;
        }
        return ret;
    }
}