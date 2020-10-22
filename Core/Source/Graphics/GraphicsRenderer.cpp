#include "GraphicsRenderer.h"
#include "Platform/Api/Window.h"
#include "Resources/Resources.h"
#include "Graphics/RenderSurface.h"
#include "Core/Engine.h"

namespace Forge
{
	void GraphicsRenderer::SetupScreenPresenter()
	{
		renderSurface = RenderSurface::Create();
		renderSurface->SetFramebufferSize(size);
		renderSurface->Generate();
		screenMaterial.SetShader(engine->getResources()->LoadNowResource<Shader>("Resources/Shaders/ScreenShader.glsl"));
		screenMaterial.GetShader()->Compile();
        screenMaterial.GetUniform("ScreenTexture")->SetTexture(*renderSurface->GetColorTexture());

		float tmp[] =
		{
			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f
		};
		uint ib[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		screenMesh.SetVertexBuffer(tmp, 16, BufferUsage::STATIC);
		screenMesh.SetIndexBuffer(ib, 6);
		BufferLayout bf;
		bf.Add<float>("pos", 0, 2, BufferElementType::Position);
		bf.Add<float>("TxtrCoord", 1, 2, BufferElementType::UV);
		screenMesh.SetBufferLayout(bf);
		screenMesh.Initialize();
	}

	GraphicsRenderer::GraphicsRenderer()
	{}

	GraphicsRenderer::~GraphicsRenderer()
	{}

	void GraphicsRenderer::Init(const Vector2i& windowSize)
	{
		size = windowSize;
	}
}
