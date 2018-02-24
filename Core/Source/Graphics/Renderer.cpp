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
#if defined(WIN32)
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

	void Renderer::AddDrawBatch(DrawBatch* drawBatch)
	{
		drawBatches.push_back(drawBatch);
	}

	void Renderer::Draw()
	{
		deviceRenderer->PreDraw();

		for (uint i = 0; i < drawBatches.size(); i++)
		{
			deviceRenderer->Draw(drawBatches[i]);
		}
		deviceRenderer->PostDraw();

		deviceRenderer->DrawToScreen();
	}

	bool Renderer::RemoveDrawBatch(DrawBatch* drawBatch)
	{
		if (ContainsDrawBatch(drawBatch))
		{
			auto it = std::find(drawBatches.begin(), drawBatches.end(), drawBatch);
			drawBatches.erase(it);
			return true;
		}

		return false;
	}

	bool Renderer::ContainsDrawBatch(DrawBatch* drawBatch)
	{
		return std::find(drawBatches.begin(), drawBatches.end(), drawBatch) != drawBatches.end();
	}

	void Renderer::SetSize(const Vector2i& newSize)
	{
		deviceRenderer->SetSize(newSize);
	}

	Renderer::Renderer()
	{}

	Renderer::~Renderer()
	{
		for(uint i = 0; i < drawBatches.size(); i++)
		{
			delete drawBatches[i];
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
