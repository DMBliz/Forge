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

        std::map<int, Window*> windows;

        int lastID = 0;

    public:
        MacOSWindowSystem() = default;
        virtual ~MacOSWindowSystem();

        void init() override;

        void update() override;

        Window* createWindow(const WindowCreationDesc& desc) override;

        Window* getWindowByName(const String& name) override;
        Window* getWindowByID(int ID) override;

        void destroyWindow(Window* window) override;

        Cursor* createCursor(SystemCursor cursorType) override;

        Cursor* createCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot) override;

        const String& getClipboardString() override;

        void setClipboardString(const String& data) override;
    };
}