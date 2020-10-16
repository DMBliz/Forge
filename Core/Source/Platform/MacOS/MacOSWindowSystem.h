//
// Created by Dmitry Metelitsa on 10/17/20.
//

#pragma once

#include "Platform/Api/WindowSystem.h"

#if defined(__OBJC__)
@class NSAutoreleasePool;
@class NSApplication;

typedef NSApplication* NSApplicationPtr;
typedef NSAutoreleasePool* NSAutoreleasePoolPtr;
#else
#include <objc/NSObjCRuntime.h>
typedef id NSApplicationPtr;
typedef id NSAutoreleasePoolPtr;
#endif

namespace Forge
{
    class MacOSWindowSystem : public WindowSystem
    {
    private:
        NSApplicationPtr application = nullptr;
        NSAutoreleasePoolPtr pool = nullptr;
        bool isInitialized = false;

        std::vector<Window*> windows;

    public:
        MacOSWindowSystem() = default;
        virtual ~MacOSWindowSystem();

        void init() override;

        void update() override;

        Window* createWindow(const WindowCreationDesc& desc) override;

        Cursor* createCursor(SystemCursor cursorType) override;

        Cursor* createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot) override;

        const String& getClipboardString() override;

        void setClipboardString(const String& data) override;
    };
}