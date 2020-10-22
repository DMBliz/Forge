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

class SandboxApp : public Forge::Application
{
private:
    Window* win;
    Window* win2;
    Context* ctx;
    Context* ctx2;
    Sprite* spr;
    InputManager* manager;
    WindowSystem* ws;

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

        DeviceCapabilities* deviceInfo = api->getApi<DeviceCapabilities>("DeviceCapabilities");
        GraphicsApiType gapi = deviceInfo->getSupportedApi();

        ws = api->getApi<WindowSystem>("WindowSystem");
        win = ws->createWindow(WindowCreationDesc("Test window",
                RectI(0, 0, 800, 600), Forge::WindowState::WINDOWED));

        ContextApi* contextApi = api->getApi<ContextApi>("ContextApi");
        ctx = contextApi->createContext(gapi);
        win->setContext(ctx);
        ctx->setActive();

        win2 = ws->createWindow(WindowCreationDesc("window 2",
                RectI(50, 50, 200, 300), WindowState::WINDOWED));
        ctx2 = contextApi->createContext(gapi);
        win2->setContext(ctx2);
        ctx2->setActive();

        ctx->setActive();

        Resources* res = engine->getResources();

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

        win->onActiveStateChanged.Add<SandboxApp, &SandboxApp::windowActiveStateChanged>(this);

        arrowCursor = ws->createCursor(SystemCursor::Arrow);
        handCursor = ws->createCursor(SystemCursor::Hand);
        verticalCursor = ws->createCursor(SystemCursor::VerticalResize);
        horizontalCursor = ws->createCursor(SystemCursor::HorizontalResize);
        crossCursor = ws->createCursor(SystemCursor::Cross);
        ibeamCursor = ws->createCursor(SystemCursor::IBeam);

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
                LOG_INFO("Maximized");
                break;
            case WindowState::FULLSCREEN:
                LOG_INFO("FULLSCREEN");
                break;
            case WindowState::WINDOWED:
                LOG_INFO("WINDOWED");
                break;
            case WindowState::FULLSCREEN_BORDERLESS:
                LOG_INFO("FULLSCREEN_BORDERLESS");
                break;
        }
    }

    void minimizeChanged(Window* window, bool minimized)
    {
        if(minimized)
        {
            LOG_INFO("minimized");
        }
        else
        {
            LOG_INFO("deminimized");
        }
    }

    void windowSizeChanged(Window* window, const RectI& size)
    {
        std::cout << "size:" << size.toString() << std::endl;
    }

    void windowResolutionChanged(Window* window, const Vector2i& resolution)
    {
        std::cout << "resolution:" << resolution.ToString() << std::endl;
    }

    void windowActiveStateChanged(Window* window, bool active)
    {
        std::cout << "window " << window->getTitle() << " is now " << (active ? "active" : "inactive") << std::endl;
    }


    void update() override
    {
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
        manager->update();
    }


    void draw() override
    {
        ctx->setActive();
        spr->Draw();
        engine->getRenderer()->Draw();

        ctx2->setActive();
        spr->Draw();
        engine->getRenderer()->Draw();

        ws->update();
    }

    void stop() override
    {

    }
};

Forge::Application* Forge::getApplication()
{
    return new SandboxApp();
}
