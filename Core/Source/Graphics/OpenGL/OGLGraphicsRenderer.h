#pragma once
#include "Graphics/GraphicsRenderer.h"
#include "glad/glad.h"

namespace Forge
{

	class OGLGraphicsRenderer : public GraphicsRenderer
	{
	private:

		GLuint frameBufferId = 0;
		GLsizei frameBufferWidth = 0;
		GLsizei frameBufferHeight = 0;

		GLbitfield clearMask = 0;
		GLfloat frameBufferClearColor[4];
		void CreateProgram();

		
	public:
		OGLGraphicsRenderer();
		~OGLGraphicsRenderer();

		void PreDraw() override;
		void Draw(Mesh* mesh, Material* material) override;
		void PostDraw() override;

		void Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer) override;

		void SetSize(const Vector2i& newSize) override;
		void SetClearColorBuffer(bool value) override;
		void SetClearDepthBuffer(bool value) override;
		void SetClearColor(const Color& color) override;

		void BindFrameBuffer(GLuint bufferId);
		void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);
		void SetClearColorValue(const float* clearColorValue);
		void SetClearDepthValue(float clearDepthValue);
		void SetDepthMask(bool value);


	};

}
