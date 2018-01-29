#include "Renderer.h"
#include "Platform/Window.h"
#include "GraphicsRenderer.h"
#include "Core/Engine.h"

namespace Forge
{

	void Renderer::Init(Window* win)
	{
#if defined(WIN32)
#if defined(OGL)
		deviceRenderer = GraphicsRenderer::Create();
#elif defined(DX)
#endif
#elif defined(MACOS)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
		deviceRenderer->Init(*win);
	}

	void Renderer::SetProjectionMatrix(const Matrix4& projection)
	{
		deviceRenderer->SetProjection(projection);
	}

	void Renderer::SetPerspectiveProjection(float fov, float nearf, float farf)
	{
		const Vector2i wsize = engine->GetWindow()->GetSize();
		SetProjectionMatrix(Matrix4::Perspective(fov, wsize.x / wsize.y, nearf, farf));
	}

	void Renderer::SetOrthographicProjection(float nearf, float farf)
	{
		const Vector2i wsize = engine->GetWindow()->GetSize();
		SetProjectionMatrix(Matrix4::Orthographic(0, wsize.x, 0, wsize.y, nearf, farf));
	}

	void Renderer::SetViewMatrix(const Matrix4& view)
	{
		deviceRenderer->SetView(view);
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

}
