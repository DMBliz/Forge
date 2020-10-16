#pragma once
#include "Platform/Api/Window.h"
#include "Types.h"

#if defined(__OBJC__)
#import <Cocoa/Cocoa.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Platform/Api/Cursor.h>

@class MacOSView;
typedef NSWindow* NSWindowPtr;
typedef MacOSView* NSViewPtr;
typedef id<NSWindowDelegate> NSWindowDelegatePtr;
typedef NSScreen* NSScreenPtr;
#else
#include <objc/NSObjCRuntime.h>
typedef id NSWindowPtr;
typedef id NSViewPtr;
typedef id NSWindowDelegatePtr;
typedef id NSScreenPtr;
typedef uint32 CGDirectDisplayID;
#endif

namespace Forge
{

    class MacOSWindow : public Window
    {
    public:
        MacOSWindow();

        void create(const WindowCreationDesc& creationDesc) override;
        void close() override;

        void platformUpdate() override;

        void bringToFront();
        void show() override;
        void hide() override;
        void setMinimized(bool value) override;

        void setWindowState(WindowState windowState) override;

        InputManager* getInput() override;

        void setCursor(Cursor* cursor) override;

        void setWindowRect(const RectI& newSize) override;

        void setTitle(const String& newTitle) override;

        void handleResignKeyChange();
        void handleBecomeKeyChange();
        void handleScreenChange();
        void handleScaleFactorChange();
        void handleFullscreenChange(bool fullscreen);
        void handleDeminiaturize();
        void handleMiniaturize();
        void handleClose();
        void handleResize();

        const NSRect& getWindowFrame() const;

        void setContentView(MacOSView* view);
        NSView* getContentView() const;

        NSViewPtr getNativeView() const;
        CGDirectDisplayID getDisplayID() const;

        virtual ~MacOSWindow();

    private:
        void resetWindowState();
        void onWindowEventsFinished();

        InputManager input;
        NSWindowPtr window = nil;
        NSViewPtr view = nil;
        NSWindowDelegatePtr windowDelegate = nil;
        NSScreenPtr screen = nil;
        CGDirectDisplayID displayId = 0;
        NSUInteger windowStyleMask = 0;
        NSRect windowFrame;

        bool fullscreen = false;
        bool borderlessFullscreen = false;
        bool maximized = false;
        bool windowed = false;

        NSApplicationPtr application = nullptr;
        NSAutoreleasePoolPtr pool = nullptr;
    };

}