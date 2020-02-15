#pragma once
#include "Math/Vector2i.h"
#include "Containers/String.h"
#include <mutex>
#include <Math/RectI.h>
#include "Defines.h"
#include "EventSystem/Event.h"
#include "Context.h"
#include "Math/Vector2.h"
#include "Input.h"

namespace Forge
{
    enum class WindowState
    {
        WINDOWED,
        MAXIMIZED,
        FULLSCREEN
    };

    struct WindowCreationDesc
    {
        String title;
        RectI size;
        WindowState openState;
        bool resizable;
        bool highDPI;

        WindowCreationDesc(const String& title, const RectI& size,
                           WindowState state = WindowState::FULLSCREEN, bool resizable= true, bool highDPI = true)
                : title(title), size(size), openState(openState), resizable(resizable), highDPI(highDPI)
        { }
    };

    class Window
    {
        friend class Input;
    public:
        Event<void(Window*, const Vector2i&)> onSizeChanged;
        Event<void(Window*)> onBecameFullScreen;
        Event<void(Window*)> onWindowed;
        Event<void(Window*)> onActiveStateChanged;

    protected:
        Input* input;
        RectI windowSize;
        Vector2i resolution;

        float contentScale = 1.0f;
        WindowState windowState;
        bool resizable = false;
        bool highDPI = true;
        String windowTitle;
        Context* context;

        bool hasFocus = true;
        bool minimized = false;

        virtual void setCursorPosition(const Vector2i& newPos) = 0;
    public:
        virtual void create(const WindowCreationDesc& creationDesc) = 0;
        virtual void close() = 0;

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual void platformUpdate() = 0;

        virtual void setClipboard(const String& data) = 0;
        virtual const String& getClipboard() = 0;

        virtual void setMinimized(bool value)
        {
            minimized = value;
        }

        const RectI& getSize() const
        {
            return windowSize;
        }
        virtual void setSize(const RectI& newSize)
        {
            windowSize = newSize;
        }

        const Vector2i& getResolution() const
        {
            return resolution;
        }
        float getContentScale() const
        {
            return contentScale;
        }

        virtual void setWindowState(WindowState windowState)
        {
            this->windowState = windowState;
        }

        bool isFocused() const
        {
            return hasFocus;
        }
        void setFocused(bool focused)
        {
            hasFocus = true;
        }

        const String& getTitle() const
        {
            return windowTitle;
        }
        virtual void setTitle(const String& newTitle)
        {
            windowTitle = newTitle;
        }

        bool isHightDpi() const
        {
            return highDPI;
        }
    };
}
