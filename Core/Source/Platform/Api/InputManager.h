//
// Created by Dmitry Metelitsa on 2/26/20.
//

#pragma once

#include <map>
#include "InputDevice.h"

namespace Forge
{

    class InputManager
    {
    private:
        std::map<InputDeviceType, InputDevice*> devices;
    public:
        void registerDevice(InputDevice* device);

        void update();

        template<typename T>
        T* getDevice(InputDeviceType type)
        {
            return (T*)devices[type];
        }
    };
}
