#include "GraphicsRenderer.h"
#include "Platform/Window.h"
#include "OpenGL/GLGraphicsRenderer.h"
#include "Shader.h"
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
		//engine->GetWindow()->onSizeChanged.Add<GraphicsRenderer, &GraphicsRenderer::SetSize>(this);
		screenMaterial.SetShader(engine->GetResources()->LoadNowResource<Shader>("Resources/Shaders/ScreenShader.glsl"));
		screenMaterial.AddTexture(renderSurface->GetColorTexture(), "ScreenTexture");
		screenMaterial.Uniforms().AddUniform("ScreenTexture", UniformDataType::SAMPLER2D);
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
		bf.Add<float>("pos", 0, 2, false);
		bf.Add<float>("TxtrCoord", 1, 2, false);
		screenMesh.SetBufferLayout(bf);
		screenMesh.Initialize();
	}

	GraphicsRenderer::GraphicsRenderer()
	{}

	GraphicsRenderer::~GraphicsRenderer()
	{}

	void GraphicsRenderer::Init(const Vector2i& windowSize)
	{
		frustum.SetSize(windowSize);
		frustum.CalculateMatrix();
		size = windowSize;
	}

	GraphicsRenderer* GraphicsRenderer::Create()
	{
#if defined(OGL)
		return new GLGraphicsRenderer();
#elif defined(DX) //TODO: return for DX
		return nullptr;
#endif
	}
}
