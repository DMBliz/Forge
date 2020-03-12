//
// Created by Дмитрий Метелица on 2019-11-19.
//

#pragma once

#include <Math/RectI.h>
#include "Window.h"
#include "Api.h"
#include "DeviceCapabilities.h"
#include "Cursor.h"

namespace Forge
{

    class WindowSystem : public Api
    {
    public:
        virtual ~WindowSystem();

        virtual void init();

        Window* createWindow(const WindowCreationDesc& desc);

        Cursor* createCursor(SystemCursor cursorType);
        Cursor* createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot);

    };
}