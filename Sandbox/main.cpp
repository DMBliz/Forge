#include <thread>
#include <Platform/DefaultApplication.h>
#include <Platform/Api/DeviceCapabilities.h>
#include <Graphics/Renderer.h>
#include <Platform/Api/ContextApi.h>
#include <Core/Engine.h>
#include <Graphics/Sprite.h>

using namespace Forge;
//nested serialize method with ISerializable



class SandboxApp : public Forge::DefaultApplication
{
private:
    Window* win;
    Context* ctx;
    Sprite* spr;
public:
    void start() override
    {
        PlatformApiProvider* api = getPlatformApiProvider();

        WindowSystem* windowSystem = api->getApi<WindowSystem>("WindowSystem");
        win = windowSystem->createWindow(WindowCreationDesc("Test window",
                RectI(0, 0, 800, 600), Forge::WindowState::WINDOWED));

        DeviceCapabilities* deviceInfo = api->getApi<DeviceCapabilities>("DeviceCapabilitiesApi");
        GraphicsApiType gapi = deviceInfo->getSupportedApi();

        ContextApi* contextApi = api->getApi<ContextApi>("ContextApi");
        ctx = contextApi->createContext(gapi);
        ctx->CreateContext(*win, 1);
        ctx->setActive();

        Resources* res = engine->GetResources();

        Renderer* render = new Renderer(gapi);
        render->Init(win->getResolution());

        Texture2D* tex = res->LoadNowResource<Texture2D>("Resources/awesomeface.png");
        Shader* sh = res->LoadNowResource<Shader>("Resources/Shaders/SpriteShader.glsl");
        sh->Compile();

        engine->setRender(render);

        spr = new Sprite();
        Material* mat = new Material();
        mat->SetShader(sh);
        mat->SetShader(sh);
        spr->SetMaterial(mat);
        Matrix3x4* m = new Matrix3x4(Vector3(0,0, 1), Quaternion(), Vector3(1,1,1));
        spr->SetWorldPosition(*m);
        spr->SetTexture(tex);


        switch (gapi)
        {
            case GraphicsApiType::Vulkan:
                LOG_INFO("Using Vulkan api");
                break;
            case GraphicsApiType::OpenGL:
                LOG_INFO("Using Opengl api");
                break;
        }
    }

    void update() override
    {
        win->platformUpdate();
        spr->Draw();
        engine->GetRenderer()->Draw();
        ctx->PlatformUpdate();

    }

    void stop() override
    {

    }


};

Forge::Application* Forge::getApplication()
{
    return new SandboxApp();
}
