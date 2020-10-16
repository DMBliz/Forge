//
// Created by Dmitry Metelitsa on 1/29/20.
//

#include "Application.h"


namespace Forge
{
    PlatformApiProvider* Application::createPlatformApiProvider()
    {
        return new PlatformApiProvider();
    }
}