//
// Created by Дмитрий Метелица on 2/11/20.
//

#include "OSXContextApi.h"
#if defined(OGL)
#include "Platform/OSX/Context/OGL/OGLOSXContext.h"
#endif
#if defined(VK)
//TODO: include vulkan context
#endif

namespace Forge
{
    Context* OSXContextApi::createContext(GraphicsApiType gapi)
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
                ret = new OGLOSXContext();
#endif
                break;
        }
        return ret;
    }
}