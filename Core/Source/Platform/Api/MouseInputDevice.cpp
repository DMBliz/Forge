//
// Created by Дмитрий Метелица on 2/26/20.
//

#include "MouseInputDevice.h"

namespace Forge
{
    void Forge::MouseInputDevice::update()
    {
        uint buttonCount = static_cast<uint>(MouseButton::ButtonCount);

        for (int i = 0; i < buttonCount; ++i)
        {
            if ((prevMouseButtons[i] == KeyState::Down && mouseButtons[i] == KeyState::Down) ||
                (prevMouseButtons[i] == KeyState::Hold && mouseButtons[i] == KeyState::Hold) ||
                (prevMouseButtons[i] == KeyState::Hold && mouseButtons[i] == KeyState::Down))
                mouseButtons[i] = KeyState::Hold;

            if (prevMouseButtons[i] == KeyState::Up)
                mouseButtons[i] = KeyState::None;

            prevMouseButtons[i] = mouseButtons[i];
        }
    }

    void Forge::MouseInputDevice::sendEvent(const MouseEvent& event)
    {
        mouseButtons[static_cast<uint>(event.button)] = event.state;
    }

    void MouseInputDevice::mousePositionChanged(const Vector2& newPosition)
    {
        mousePosition = newPosition;
    }

    void MouseInputDevice::wheelScrolled(const Vector2& wheelDelta)
    {
        this->wheelDelta = wheelDelta;
    }

    KeyState Forge::MouseInputDevice::getKeyState(MouseButton key) const
    {
        return mouseButtons[static_cast<uint>(key)];
    }

    const Vector2& Forge::MouseInputDevice::getMousePosition() const
    {
        return mousePosition;
    }

    const Vector2& MouseInputDevice::getWheelDelta() const
    {
        return wheelDelta;
    }

    InputDeviceType MouseInputDevice::getType()
    {
        return InputDeviceType::Mouse;
    }
}
