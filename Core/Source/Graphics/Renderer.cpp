#include "Renderer.h"
#include "Platform/Window.h"
#include "GraphicsRenderer.h"
#include "Core/Engine.h"

namespace Forge
{

	void Renderer::Init(const Vector2i& windowSize)
	{
		if (_deviceRenderer != nullptr)
			delete _deviceRenderer;
#if defined(_WIN32)
#if defined(OGL)
		_deviceRenderer = GraphicsRenderer::Create();
#elif defined(DX)
#endif
#elif defined(MACOS)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		_deviceRenderer->Init(windowSize);

        _frustum.SetSize(windowSize);
        _frustum.CalculateMatrix();
	}

    void Renderer::AddLight(PointLight* light)
    {
        auto it = std::find(_pointLights.begin(), _pointLights.end(), light);
        if (it == _pointLights.end())
            _pointLights.push_back(light);
    }

    void Renderer::AddLight(SpotLight* light)
    {
        auto it = std::find(_spotLights.begin(), _spotLights.end(), light);
        if (it == _spotLights.end())
            _spotLights.push_back(light);
    }

    void Renderer::AddLight(DirectionalLight* light)
    {
        auto it = std::find(_dirLights.begin(), _dirLights.end(), light);
        if (it == _dirLights.end())
            _dirLights.push_back(light);
    }

    void Renderer::RemoveLight(PointLight* light)
    {
        auto it = std::find(_pointLights.begin(), _pointLights.end(), light);
        if (it != _pointLights.end())
            _pointLights.erase(it);
    }

    void Renderer::RemoveLight(SpotLight* light)
    {
        auto it = std::find(_spotLights.begin(), _spotLights.end(), light);
        if (it != _spotLights.end())
            _spotLights.erase(it);
    }

    void Renderer::RemoveLight(DirectionalLight* light)
    {
        auto it = std::find(_dirLights.begin(), _dirLights.end(), light);
        if (it != _dirLights.end())
            _dirLights.erase(it);
    }

    void Renderer::Draw()
	{
		_deviceRenderer->PreDraw();

		for (uint i = 0; i < _drawBuffer.size(); i++)
		{
            _drawBuffer[i]._material->Use();
            _drawBuffer[i]._mesh->Bind();
			_deviceRenderer->Draw(_drawBuffer[i]._mesh->GetIndexBufferSize());
		}

        for(std::map<float, DrawCommand>::reverse_iterator it = _transparentBuffer.rbegin(); it != _transparentBuffer.rend(); ++it)
        {
            it->second._material->Use();
            it->second._mesh->Bind();
            _deviceRenderer->Draw(it->second._mesh->GetIndexBufferSize());
        }

		_deviceRenderer->PostDraw();
		_deviceRenderer->DrawToScreen();

        _drawBuffer.clear();
        _transparentBuffer.clear();
	}

    const std::vector<DirectionalLight*>& Renderer::GetDirLights() const
    {
        return _dirLights;
    }

    const std::vector<PointLight*>& Renderer::GetPointLights() const
    {
        return _pointLights;
    }

    const std::vector<SpotLight*>& Renderer::GetSpotLights() const
    {
        return _spotLights;
    }

    void Renderer::SetSize(const Vector2i& newSize)
	{
        _frustum.SetSize(newSize);
        _frustum.CalculateMatrix();
		_deviceRenderer->SetSize(newSize);
        
	}

	Renderer::Renderer()
	{}

	Renderer::~Renderer()
	{}

	void Renderer::SetFrustum(const Frustum& frustum)
	{

        this->_frustum = frustum;
	}

	const Frustum& Renderer::GetFrustum() const
	{
		return _frustum;
	}

    void Renderer::PushCommand(DrawCommand command)
    {
        if(command.transparent)
        {
            Vector3 cam = GetCamera().GetPosition();
            Vector3 pos = command.worldTransform.GetTranslation();
            _transparentBuffer[(cam - pos).LengthSquared()] = command;
        }
	    else
        {
            _drawBuffer.push_back(command);
        }

    }

    void Renderer::SetWindowClearColor(const Color& color)
	{
		_deviceRenderer->SetClearColor(color);
	}

	const Color& Renderer::GetWindowClearColor()
	{
		return _deviceRenderer->GetClearColor();
	}

	void Renderer::SetFrameBufferClearColor(const Color& color)
	{
		_deviceRenderer->GetSurface()->SetClearColor(color);
	}

	const Color& Renderer::GetFrameBufferClearColor()
	{
		return _deviceRenderer->GetSurface()->GetClearColor();
	}
}
