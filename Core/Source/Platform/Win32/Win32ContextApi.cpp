//
// Created by dimon on 2/15/2020.
//

#include "Win32ContextApi.h"
#if defined(OGL)
#include "Platform/Win32/Context/OGL/OGLWin32Context.h"
#endif
#if defined(VK)
//TODO: include vulkan context
#endif

namespace Forge
{
    Context* Win32ContextApi::createContext(GraphicsApiType gapi)
    {
        Context* ret;
        switch(gapi)
        {
            case GraphicsApiType::Vulkan:
#if defined(VK)

#endif
                //For now we have only opengl render
            case GraphicsApiType::OpenGL:
#if defined(OGL)
                ret = new OGLWin32Context();
#endif
                break;
        }
        return ret;
    }
}