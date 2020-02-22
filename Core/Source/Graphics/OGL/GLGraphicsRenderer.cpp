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

		renderSurface->SetClearColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void GLGraphicsRenderer::PreDraw()
	{
		renderSurface->Bind();
		
		ClearFrameBuffer(renderSurface->GetClearColor());
		const Vector2i& size = renderSurface->GetSize();
        SetBlending(_blending);
        SetCullFace(_cullFace);
		glEnable(GL_DEPTH_TEST);
		SetDepthMask(true);
		ClearDepthValue(clearDepth);
		glDepthFunc(GL_LESS);
		glCheck(glClear(clearMask));
	}

	void GLGraphicsRenderer::Draw(uint count)
	{
        glCheck(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void GLGraphicsRenderer::PostDraw()
	{
		BindFrameBuffer(0);
	}

	void GLGraphicsRenderer::DrawToScreen()
	{
		ClearFrameBuffer(clearColor);
		SetDepthMask(false);
		glDisable(GL_DEPTH_TEST);
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

    void GLGraphicsRenderer::SetBlending(bool value)
    {
        GraphicsRenderer::SetBlending(value);

        if(value)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
	    else
        {
            glDisable(GL_BLEND);
        }
    }

    void GLGraphicsRenderer::SetCullFace(bool value)
    {
        GraphicsRenderer::SetCullFace(value);
        if(value)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
        }
		else
        {
            glDisable(GL_CULL_FACE);
        }
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
