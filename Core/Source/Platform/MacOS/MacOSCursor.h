//
// Created by Dmitry Metelitsa on 3/11/20.
//

#pragma once
#include "Platform/Api/Cursor.h"
#if defined(__OBJC__)
#  import <AppKit/AppKit.h>
typedef NSCursor* NSCursorPtr;
#else
#  include <objc/objc.h>
typedef id NSCursorPtr;
#endif

namespace Forge
{
    class MacOSCursor : public Cursor
    {
    private:
        NSCursorPtr cursor;
    public:
        MacOSCursor(SystemCursor cursor);
        MacOSCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot);

        NSCursorPtr getNativeCursor();
    };
}
