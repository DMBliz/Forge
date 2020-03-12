#pragma once
#include "Platform/Api/Window.h"
#include "Types.h"

#if defined(__OBJC__)
#import <Cocoa/Cocoa.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Platform/Api/Cursor.h>

@class OSXView;
typedef NSWindow* NSWindowPtr;
typedef OSXView* NSViewPtr;
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

    class OSXWindow : public Window
    {
    public:
        OSXWindow();

        void create(const WindowCreationDesc& creationDesc) override;
        void close() override;

        void platformUpdate() override;

        void setClipboard(const String& data) override;
        const String& getClipboard() override;

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

        void setContentView(OSXView* view);
        NSView* getContentView() const;

        NSViewPtr getNativeView() const;
        CGDirectDisplayID getDisplayID() const;

        virtual ~OSXWindow();

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