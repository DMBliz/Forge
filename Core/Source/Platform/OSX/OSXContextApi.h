//
// Created by Дмитрий Метелица on 2/11/20.
//

#pragma once

#include <Platform/Api/ContextApi.h>

namespace Forge
{

    class OSXContextApi : public ContextApi
    {
    public:
        Context* createContext(GraphicsApiType gapi) override;
    };

}
