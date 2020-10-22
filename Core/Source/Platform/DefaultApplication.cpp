//
// Created by Dmitry Metelitsa on 2/4/20.
//

#include <Platform/Api/DeviceCapabilities.h>
#include <Platform/Api/WindowSystem.h>
#include <Platform/Api/ContextApi.h>
#include <Graphics/Renderer.h>
#include <Core/Engine.h>
#include "DefaultApplication.h"

namespace Forge
{
    void DefaultApplication::start()
    {
        PlatformApiProvider* api = getPlatformApiProvider();

        DeviceCapabilities* deviceInfo = api->getApi<DeviceCapabilities>("DeviceCapabilities");
        GraphicsApiType gapi = deviceInfo->getSupportedApi();

        windowSystem = api->getApi<WindowSystem>("WindowSystem");
        mainWindow = windowSystem->createWindow(WindowCreationDesc("Test window",
                                                  RectI(0, 0, 800, 600), Forge::WindowState::WINDOWED));

        mainWindow->onMinimizeChanged.Add<DefaultApplication, &DefaultApplication::windowMinimizeChanged>(this);

        ContextApi* contextApi = api->getApi<ContextApi>("ContextApi");
        Context* ctx = contextApi->createContext(gapi);
        mainWindow->setContext(ctx);
        ctx->setActive();

        inputManager = mainWindow->getInput();

        Renderer* render = new Renderer(gapi);
        render->Init(mainWindow->getResolution());
        engine->setRender(render);

        onStart();
    }

    void DefaultApplication::update()
    {
        inputManager->update();
        onUpdate();
    }

    void DefaultApplication::draw()
    {
        onDraw();

        renderer->Draw();
        windowSystem->update();
    }

    void DefaultApplication::stop()
    {
        onStop();
        windowSystem->destroyWindow(mainWindow);

    }

    void DefaultApplication::windowMinimizeChanged(Window* window, bool minimized)
    {
        if (minimized)
        {
            onSuspend();
        }
        else
        {
            onResume();
        }
    }
}