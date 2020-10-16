//
// Created by Dmitry Metelitsa on 2/25/20.
//

#pragma once

namespace Forge
{
    enum class InputDeviceType
    {
        Keyborad,
        Mouse,
        Gamepad,
        Touch
    };

    enum class KeyState
    {
        None,
        Down,
        Hold,
        Up
    };

    class InputDevice
    {
    public:
        virtual void update() = 0;
        virtual InputDeviceType getType() = 0;

    };
}
