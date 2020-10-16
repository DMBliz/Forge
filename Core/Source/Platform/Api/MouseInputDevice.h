//
// Created by Dmitry Metelitsa on 2/25/20.
//
#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Types.h"
#include "InputDevice.h"

namespace Forge
{

    enum class MouseButton
    {
        None = -1,
        Left = 0,
        Right,
        Middle,
        XButton1,
        XButton2,

        ButtonCount
    };

    struct MouseEvent
    {
        MouseButton button;
        KeyState state;
    };

    class MouseInputDevice : public InputDevice
    {
    private:
        KeyState mouseButtons[static_cast<uint>(MouseButton::ButtonCount)];
        KeyState prevMouseButtons[static_cast<uint>(MouseButton::ButtonCount)];

        Vector2 mousePosition;
        Vector2 wheelDelta;
    public:
        void update() override;

        void sendEvent(const MouseEvent& event);
        void mousePositionChanged(const Vector2& newPosition);
        void wheelScrolled(const Vector2& wheelDelta);

        KeyState getKeyState(MouseButton key) const;
        const Vector2& getMousePosition() const;
        const Vector2& getWheelDelta() const;

        InputDeviceType getType() override;
    };
}
