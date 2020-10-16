//
// Created by Dmitry Metelitsa on 2/5/20.
//

#pragma once

#include <Math/Vector2i.h>
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
        Vector2i screenSize;
    public:
        const Vector2i& getScreenSize() const;

        void init() override;
        GraphicsApiType getSupportedApi();
    };
}

