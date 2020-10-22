//
// Created by Dmitry Metelitsa on 1/29/20.
//

#pragma once

#include "Platform/Api/PlatformApiProvider.h"

namespace Forge
{
    class Application
    {
    protected:
        virtual PlatformApiProvider* createPlatformApiProvider();
    public:
        virtual void start() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void stop() = 0;

        PlatformApiProvider* getPlatformApiProvider()
        {
            static PlatformApiProvider* provider = createPlatformApiProvider();
            return provider;
        }
    };

    Forge::Application* getApplication();
}
