#include "OGLContext.h"

namespace Forge
{

	OGLContext::OGLContext()
	{}


	OGLContext::~OGLContext()
	{}


	void OGLContext::Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer)
	{
		Context::Init(win, sampleCount, depth, debugRenderer);

		frameBufferWidth = size.x;
		frameBufferHeight = size.y;

		clearMask = 0;
		if (Context::clearColorBuffer) clearMask |= GL_COLOR_BUFFER_BIT;
		if (Context::clearDepthBuffer) clearMask |= GL_DEPTH_BUFFER_BIT;

		clearColor = Color(0.2f, 0.3f, 0.3f, 1.0f);

		frameBufferClearColor[0] = clearColor.NormalizedR();
		frameBufferClearColor[1] = clearColor.NormalizedG();
		frameBufferClearColor[2] = clearColor.NormalizedB();
		frameBufferClearColor[3] = clearColor.NormalizedA();

	}

	void OGLContext::Draw()
	{
		BindFrameBuffer(frameBufferId);
		SetViewport(0, 0, frameBufferWidth, frameBufferHeight);
		SetClearColorValue(frameBufferClearColor);
		SetDepthMask(true);
		SetClearDepthValue(clearDepth);
		glClear(clearMask);
		
	}

	void OGLContext::SetSize(const Vector2i& newSize)
	{
		Context::SetSize(newSize);

		frameBufferWidth = newSize.x;
		frameBufferHeight = newSize.y;
	}

	void OGLContext::SetClearColorBuffer(bool value)
	{
		Context::SetClearColorBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_COLOR_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT);
	}

	void OGLContext::SetClearDepthBuffer(bool value)
	{
		Context::SetClearDepthBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_DEPTH_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT);
	}

	void OGLContext::SetClearColor(const Color& color)
	{
		Context::SetClearColor(color);

		frameBufferClearColor[0] = color.NormalizedR();
		frameBufferClearColor[1] = color.NormalizedG();
		frameBufferClearColor[2] = color.NormalizedB();
		frameBufferClearColor[3] = color.NormalizedA();
	}

	void OGLContext::BindFrameBuffer(GLuint bufferId)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
	}

	void OGLContext::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glViewport(x, y, width, height);
	}

	void OGLContext::SetClearColorValue(const float* clearColorValue)
	{
		glClearColor(clearColorValue[0], clearColorValue[1], clearColorValue[2], clearColorValue[3]);
	}

	void OGLContext::SetClearDepthValue(float clearDepthValue)
	{
		glClearDepth(clearDepthValue);
	}

	void OGLContext::SetDepthMask(bool value)
	{
		glDepthMask(value ? GL_TRUE : GL_FALSE);
	}
}
