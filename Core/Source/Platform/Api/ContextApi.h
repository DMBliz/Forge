//
// Created by Dmitry Metelitsa on 2/10/20.
//

#pragma once

#include "Api.h"
#include "Context.h"
#include "DeviceCapabilities.h"

namespace Forge
{
    class ContextApi : public Api
    {
    public:
        virtual Context* createContext(GraphicsApiType gapi);
    };
}