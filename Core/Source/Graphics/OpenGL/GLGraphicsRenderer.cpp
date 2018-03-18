#include "GLGraphicsRenderer.h"
#include "Defines.h"
#include <string>
#include "Graphics/ShaderResource.h"
#include "Core/Engine.h"

#include "Graphics/Texture2DResource.h"
#include "GLCheck.h"
#include "Resources/Image.h"
#include "Graphics/Material.h"
#include "Resources/Resources.h"
#include "Graphics/RenderSurface.h"

namespace Forge
{

	GLGraphicsRenderer::GLGraphicsRenderer()
	{}


	GLGraphicsRenderer::~GLGraphicsRenderer()
	{}

	void GLGraphicsRenderer::Init(const Vector2i& windowSize)
	{
		GraphicsRenderer::Init(windowSize);


		if (!gladLoadGL())
		{
			LOG("Failed to load glad");
		}
		

		size = windowSize;

		clearMask = 0;
		if (clearColorBuffer) clearMask |= GL_COLOR_BUFFER_BIT;
		if (clearDepthBuffer) clearMask |= GL_DEPTH_BUFFER_BIT;

		clearColor = Color(0.2f, 0.3f, 0.3f, 1.0f);

		
		SetupScreenPresenter();
	}

	void GLGraphicsRenderer::PreDraw()
	{
		renderSurface->Bind();
		
		ClearFrameBuffer(renderSurface->GetClearColor());
		glEnable(GL_DEPTH_TEST);
		SetDepthMask(true);
		ClearDepthValue(clearDepth);
		glCheck(glClear(clearMask));
	}

	void GLGraphicsRenderer::Draw(Drawable* drawable)
	{
		drawable->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("projection", frustum.GetMatrix());
		drawable->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("view", camera.GetViewMatrix());
		drawable->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("model", drawable->GetWorldPosition()->ToMatrix4());

		drawable->GetMaterial().Use();
        drawable->GetMesh().Bind();
        glCheck(glDrawElements(GL_TRIANGLES, drawable->GetMesh().GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr));
		
	}

	void GLGraphicsRenderer::PostDraw()
	{
		BindFrameBuffer(0);
	}

	void GLGraphicsRenderer::DrawToScreen()
	{
		ClearFrameBuffer(clearColor);
		SetDepthMask(false);
		ClearDepthValue(clearDepth);
		glCheck(glClear(clearMask));
		if (renderToScreen)
		{
			screenMaterial.Use();
			screenMesh.Bind();
			glCheck(glDrawElements(GL_TRIANGLES, screenMesh.GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr));
		}
	}

	void GLGraphicsRenderer::SetSize(const Vector2i& newSize)
	{
		GraphicsRenderer::SetSize(newSize);
		SetViewport(0, 0, newSize.x, newSize.y);
		renderSurface->Resize(newSize);
		frustum.SetSize(newSize);
		frustum.CalculateMatrix();
	}

	void GLGraphicsRenderer::SetClearColorBuffer(bool value)
	{
		GraphicsRenderer::SetClearColorBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_COLOR_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT);
	}

	void GLGraphicsRenderer::SetClearDepthBuffer(bool value)
	{
		GraphicsRenderer::SetClearDepthBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_DEPTH_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphicsRenderer::BindFrameBuffer(GLuint bufferId)
	{
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, bufferId));
	}

	void GLGraphicsRenderer::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glCheck(glViewport(x, y, width, height));
	}

	void GLGraphicsRenderer::ClearFrameBuffer(const Color& color)
	{
		glCheck(glClearColor(color.NormalizedR(), color.NormalizedG(), color.NormalizedB(), color.NormalizedA()));
	}

	void GLGraphicsRenderer::ClearDepthValue(float clearDepthValue)
	{
		glCheck(glClearDepth(clearDepthValue));
	}

	void GLGraphicsRenderer::SetDepthMask(bool value)
	{
		glCheck(glDepthMask(value ? GL_TRUE : GL_FALSE));
	}

}
