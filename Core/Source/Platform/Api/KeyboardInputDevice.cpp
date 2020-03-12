//
// Created by Дмитрий Метелица on 2/26/20.
//

#include "KeyboardInputDevice.h"

namespace Forge
{
    void Forge::KeyboardInputDevice::update()
    {
        uint keyCount = static_cast<uint>(KeyboardKey::KeyCount);
        for (int i = 0; i < keyCount; ++i)
        {
            if ((prevKeyboardKeys[i] == KeyState::Down && keyboardKeys[i] == KeyState::Down) ||
                (prevKeyboardKeys[i] == KeyState::Hold && keyboardKeys[i] == KeyState::Hold) ||
                (prevKeyboardKeys[i] == KeyState::Hold && keyboardKeys[i] == KeyState::Down))
                keyboardKeys[i] = KeyState::Hold;

            if (prevKeyboardKeys[i] == KeyState::Up)
                keyboardKeys[i] = KeyState::None;

            prevKeyboardKeys[i] = keyboardKeys[i];
        }
    }

    void Forge::KeyboardInputDevice::sendEvent(const KeyboardEvent& event)
    {
        keyboardKeys[static_cast<uint>(event.key)] = event.state;
    }

    KeyState Forge::KeyboardInputDevice::getKeyState(KeyboardKey key) const
    {
        return keyboardKeys[static_cast<uint>(key)];
    }

    InputDeviceType KeyboardInputDevice::getType()
    {
        return InputDeviceType::Keyborad;
    }
}
