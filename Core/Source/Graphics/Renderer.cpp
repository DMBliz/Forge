#include "Renderer.h"
#include "Platform/Window.h"
#include "GraphicsRenderer.h"
#include "Core/Engine.h"

namespace Forge
{

	void Renderer::Init(const Vector2i& windowSize)
	{
		if (deviceRenderer != nullptr)
			delete deviceRenderer;
#if defined(_WIN32)
#if defined(OGL)
		deviceRenderer = GraphicsRenderer::Create();
#elif defined(DX)
#endif
#elif defined(MACOS)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		deviceRenderer->Init(windowSize);
	}

	void Renderer::AddDrawable(Drawable* drawable)
	{
		drawables.push_back(drawable);
	}

	void Renderer::Draw()
	{
		deviceRenderer->PreDraw();

		for (uint i = 0; i < drawables.size(); i++)
		{
			deviceRenderer->Draw(drawables[i]);
		}
		deviceRenderer->PostDraw();

		deviceRenderer->DrawToScreen();
	}

	bool Renderer::RemoveDrawable(Drawable* drawable)
	{
		if (ContainsDrawable(drawable))
		{
			auto it = std::find(drawables.begin(), drawables.end(), drawable);
			drawables.erase(it);
			return true;
		}

		return false;
	}

	bool Renderer::ContainsDrawable(Drawable* drawable)
	{
		return std::find(drawables.begin(), drawables.end(), drawable) != drawables.end();
	}

	void Renderer::SetSize(const Vector2i& newSize)
	{
		deviceRenderer->SetSize(newSize);
	}

	Renderer::Renderer()
	{}

	Renderer::~Renderer()
	{
		for(uint i = 0; i < drawables.size(); i++)
		{
			delete drawables[i];
		}
	}

	void Renderer::SetFrustum(const Frustum& frustum)
	{
		deviceRenderer->SetFrustum(frustum);
	}

	const Frustum& Renderer::GetFrustum() const
	{
		return deviceRenderer->GetFrustum();
	}

	void Renderer::SetWindowClearColor(const Color& color)
	{
		deviceRenderer->SetClearColor(color);
	}

	const Color& Renderer::GetWindowClearColor()
	{
		return deviceRenderer->GetClearColor();
	}

	void Renderer::SetFrameBufferClearColor(const Color& color)
	{
		deviceRenderer->GetSurface()->SetClearColor(color);
	}

	const Color& Renderer::GetFrameBufferClearColor()
	{
		return deviceRenderer->GetSurface()->GetClearColor();
	}
}
