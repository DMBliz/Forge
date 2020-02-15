//
// Created by Дмитрий Метелица on 2019-07-28.
//

#pragma once

#include "Platform/Api/Input.h"

namespace Forge
{

    class OSXInput : public Input
    {
    public:
        void SetMousePosition(const Vector2 &newPosition) override;
    };

}
