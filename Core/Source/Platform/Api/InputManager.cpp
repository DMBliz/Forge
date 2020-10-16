//
// Created by Dmitry Metelitsa on 2/26/20.
//

#include "InputManager.h"

namespace Forge
{
    void InputManager::registerDevice(InputDevice* device)
    {
        devices[device->getType()] = device;
    }

    void InputManager::update()
    {
        for(auto it = devices.begin(); it != devices.end(); it++)
        {
            it->second->update();
        }
    }
}