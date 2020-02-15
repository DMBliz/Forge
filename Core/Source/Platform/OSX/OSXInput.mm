//
// Created by Дмитрий Метелица on 2019-07-28.
//

#import <CoreGraphics/CoreGraphics.h>
#include "OSXInput.h"

namespace Forge
{
    void OSXInput::SetMousePosition(const Vector2 &newPosition)
    {
        Input::SetMousePosition(newPosition);
        CGWarpMouseCursorPosition(CGPoint{newPosition.x, newPosition.y});
    }
}