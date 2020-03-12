#pragma once
#include "Containers/String.h"
#include "Math/Vector2i.h"
#include "Math/Vector2.h"
#include "Math/RectI.h"
#include "Defines.h"
#include "EventSystem/Event.h"
#include "Context.h"
#include "InputManager.h"
#include "Cursor.h"

namespace Forge
{
    enum class WindowState
    {
        WINDOWED,
        MAXIMIZED,
        FULLSCREEN_BORDERLESS,
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
                : title(title), size(size), openState(state), resizable(resizable), highDPI(highDPI)
        { }
    };

    class Window
    {
    public:
        Event<void(Window*, const RectI&)> onWindowSizeChanged;
        Event<void(Window*, const Vector2i&)> onResolutionChanged;
        Event<void(Window*, WindowState)> onWindowStateChanged;
        Event<void(Window*, bool)> onMinimizeChanged;
        Event<void(Window*)> onWindowClose;
        Event<void(Window*)> onScreenChange;
        Event<void(Window*)> onActiveStateChanged;

    protected:
        String windowTitle;

        RectI windowRect;
        Vector2i resolution;
        float contentScale = 1.0f;
        bool highDPI = true;

        WindowState windowState;
        bool resizable = false;
        bool hasFocus = true;
        bool minimized = false;

        Cursor* currentCursor;
    public:
        virtual void create(const WindowCreationDesc& creationDesc) = 0;
        virtual void close() = 0;

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual void platformUpdate() = 0;

        virtual void setClipboard(const String& data) = 0;
        virtual const String& getClipboard() = 0;

        virtual void setCursor(Cursor* cursor)
        {
            currentCursor = cursor;
        }

        virtual Cursor* getActiveCursor()
        {
            return currentCursor;
        }

        virtual void setMinimized(bool value)
        {
            minimized = value;
        }

        const RectI& getWindowRect() const
        {
            return windowRect;
        }
        virtual void setWindowRect(const RectI& newSize)
        {
            windowRect = newSize;
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

        bool isHighDpi() const
        {
            return highDPI;
        }

        virtual InputManager* getInput() = 0;
    };
}
