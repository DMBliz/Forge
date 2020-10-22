//
// Created by Dmitry Metelitsa on 2019-11-19.
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
    protected:
        String clipboardData;
    public:
        virtual void init() = 0;

        virtual void update() = 0;

        virtual Window* createWindow(const WindowCreationDesc& desc) = 0;
        virtual Window* getWindowByName(const String& name) = 0;
        virtual Window* getWindowByID(int id) = 0;
        virtual void destroyWindow(Window* window) = 0;

        virtual Cursor* createCursor(SystemCursor cursorType) = 0;
        virtual Cursor* createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot) = 0;

        virtual const String& getClipboardString() = 0;
        virtual void setClipboardString(const String& data) = 0;
    };
}