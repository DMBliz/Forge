//
// Created by Дмитрий Метелица on 2/4/20.
//

#pragma once


#include "Application.h"

namespace Forge
{
    class DefaultApplication : public Application
    {
    protected:
        PlatformApiProvider* createPlatformApiProvider() override;

    };
}
