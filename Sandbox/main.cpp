#include <Platform/DefaultApplication.h>
#include <Platform/Api/DeviceCapabilities.h>
#include <Graphics/Renderer.h>
#include <Platform/Api/ContextApi.h>
#include <Core/Engine.h>
#include <Graphics/Sprite.h>
#include <Platform/Api/MouseInputDevice.h>
#include <Platform/Api/KeyboardInputDevice.h>
#include <Platform/Api/Cursor.h>

using namespace Forge;

class SandboxApp : public Forge::DefaultApplication
{
private:
    Window* win;
    Context* ctx;
    Sprite* spr;
    InputManager* manager;

    Cursor* arrowCursor;
    Cursor* handCursor;
    Cursor* verticalCursor;
    Cursor* horizontalCursor;
    Cursor* crossCursor;
    Cursor* ibeamCursor;

public:

    void start() override
    {
        PlatformApiProvider* api = getPlatformApiProvider();
        api->init();

        DeviceCapabilities* deviceInfo = api->getApi<DeviceCapabilities>("DeviceCapabilities");
        GraphicsApiType gapi = deviceInfo->getSupportedApi();

        WindowSystem* windowSystem = api->getApi<WindowSystem>("WindowSystem");
        win = windowSystem->createWindow(WindowCreationDesc("Test window",
                RectI(0, 0, 800, 600), Forge::WindowState::WINDOWED));

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
        manager = win->getInput();
        manager->registerDevice(new MouseInputDevice());
        manager->registerDevice(new KeyboardInputDevice());

        spr = new Sprite();
        Material* mat = new Material();
        mat->SetShader(sh);
        mat->SetShader(sh);
        spr->SetMaterial(mat);
        Matrix3x4* m = new Matrix3x4(Vector3(0,0, -5), Quaternion(0, 180, 0), Vector3(1,1,1));
        spr->SetWorldPosition(*m);
        spr->SetTexture(tex);

        win->onResolutionChanged.Add<SandboxApp, &SandboxApp::windowResolutionChanged>(this);
        win->onWindowSizeChanged.Add<SandboxApp, &SandboxApp::windowSizeChanged>(this);
        win->onWindowStateChanged.Add<SandboxApp, &SandboxApp::windowStateChanged>(this);
        win->onMinimizeChanged.Add<SandboxApp, &SandboxApp::minimizeChanged>(this);

        arrowCursor = windowSystem->createCursor(SystemCursor::Arrow);
        handCursor = windowSystem->createCursor(SystemCursor::Hand);
        verticalCursor = windowSystem->createCursor(SystemCursor::VerticalResize);
        horizontalCursor = windowSystem->createCursor(SystemCursor::HorizontalResize);
        crossCursor = windowSystem->createCursor(SystemCursor::Cross);
        ibeamCursor = windowSystem->createCursor(SystemCursor::IBeam);

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

    void windowStateChanged(Window* window, WindowState state)
    {
        switch (state)
        {
            case WindowState::MAXIMIZED:
                std::cout << "Maximized" << std::endl;
                break;
            case WindowState::FULLSCREEN:
                std::cout << "FULLSCREEN" << std::endl;
                break;
            case WindowState::WINDOWED:
                std::cout << "WINDOWED" << std::endl;
                break;
            case WindowState::FULLSCREEN_BORDERLESS:
                std::cout << "FULLSCREEN_BORDERLESS" << std::endl;
                break;
        }
    }

    void minimizeChanged(Window* window, bool minimized)
    {
        if(minimized)
        {
            std::cout << "minimized" << std::endl;
        }
        else
        {
            std::cout << "deminimized" << std::endl;
        }
    }

    void windowSizeChanged(Window* window, const RectI& size)
    {
//        std::cout << "size:" << size.toString() << std::endl;
    }

    void windowResolutionChanged(Window* window, const Vector2i& resolution)
    {
//        std::cout << "resolution:" << resolution.ToString() << std::endl;
    }

    void update() override
    {
        win->platformUpdate();
        manager->update();
        spr->Draw();
        engine->GetRenderer()->Draw();
        ctx->PlatformUpdate();

        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::A) == KeyState::Down)
        {
            win->setWindowState(WindowState::WINDOWED);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::S) == KeyState::Down)
        {
            win->setWindowState(WindowState::FULLSCREEN);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::D) == KeyState::Down)
        {
            win->setWindowState(WindowState::MAXIMIZED);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::F) == KeyState::Down)
        {
            win->setWindowState(WindowState::FULLSCREEN_BORDERLESS);
        }

        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num1) == KeyState::Down)
        {
            win->setCursor(arrowCursor);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num2) == KeyState::Down)
        {
            win->setCursor(handCursor);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num3) == KeyState::Down)
        {
            win->setCursor(verticalCursor);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num4) == KeyState::Down)
        {
            win->setCursor(horizontalCursor);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num5) == KeyState::Down)
        {
            win->setCursor(crossCursor);
        }
        if(win->getInput()->getDevice<KeyboardInputDevice>(InputDeviceType::Keyborad)->getKeyState(KeyboardKey::Num6) == KeyState::Down)
        {
            win->setCursor(ibeamCursor);
        }
    }

    void stop() override
    {

    }
};

Forge::Application* Forge::getApplication()
{
    return new SandboxApp();
}
