#pragma once
#include "Graphics/Context.h"
#include "glad/glad.h"

namespace Forge
{

	class OGLContext : public Context
	{
	private:
		GLuint frameBufferId = 0;
		GLsizei frameBufferWidth = 0;
		GLsizei frameBufferHeight = 0;
		
		GLbitfield clearMask = 0;
		GLfloat frameBufferClearColor[4];

	public:
		OGLContext();
		~OGLContext();

		virtual void Draw() override;

		virtual void Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer) override;

		virtual void SetSize(const Vector2i& newSize) override;
		virtual void SetClearColorBuffer(bool value) override;
		virtual void SetClearDepthBuffer(bool value) override;
		virtual void SetClearColor(const Color& color) override;

		void BindFrameBuffer(GLuint bufferId);
		void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);
		void SetClearColorValue(const float* clearColorValue);
		void SetClearDepthValue(float clearDepthValue);
		void SetDepthMask(bool value);
	};

}
