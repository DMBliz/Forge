//
// Created by Дмитрий Метелица on 2/5/20.
//

#pragma once

#include "Api.h"

namespace Forge
{

    enum class GraphicsApiType
    {
        OpenGL,
        Vulkan
    };

    class DeviceCapabilities : public Api
    {
    private:
        //TODO: list of supported gapi
        //sound api etc
    public:

        void init() override;
        GraphicsApiType getSupportedApi();
    };
}

