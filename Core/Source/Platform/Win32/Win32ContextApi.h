//
// Created by dimon on 2/15/2020.
//

#pragma once

#include <Platform/Api/ContextApi.h>

namespace Forge
{

    class Win32ContextApi : public ContextApi
    {
    public:
        Context *createContext(GraphicsApiType gapi) override;
    };

}
