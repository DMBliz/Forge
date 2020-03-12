//
// Created by Дмитрий Метелица on 3/11/20.
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
    class OSXCursor : public Cursor
    {
    private:
        NSCursorPtr cursor;
    public:
        OSXCursor(SystemCursor cursor);
        OSXCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot);

        NSCursorPtr getNativeCursor();
    };
}
