//
// Created by Dmitry Metelitsa on 2/4/20.
//

#pragma once


#include "Application.h"
#include "Graphics/Renderer.h"
#include "Platform/Api/WindowSystem.h"
namespace Forge
{
    class DefaultApplication : public Application
    {
    protected:
        Renderer* renderer;
        Window* mainWindow;
        WindowSystem* windowSystem;
        InputManager* inputManager;

        void windowMinimizeChanged(Window* window, bool minimized);
    public:
        void start() final;
        void update() final;
        void draw() final;
        void stop() final;

        virtual void onStart() = 0;
        virtual void onUpdate() = 0;
        virtual void onSuspend() = 0;
        virtual void onResume() = 0;
        virtual void onDraw() = 0;
        virtual void onStop() = 0;

    };
}
