#include "OGLGraphicsRenderer.h"
#include "Defines.h"
#include <string>
#include "Graphics/VertexBuffer.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/ShaderResource.h"
#include "Core/Engine.h"

#include "FileSystem/File.h"
#include "Graphics/Texture2DResource.h"
#include "GLCheck.h"
#include "Resources/Image.h"
#include "Graphics/Material.h"

namespace Forge
{

	OGLGraphicsRenderer::OGLGraphicsRenderer()
	{}


	OGLGraphicsRenderer::~OGLGraphicsRenderer()
	{}

	Shader* sh;
	Texture2DResource* tex;
	Texture2DResource* tex1;
	Mesh mesh;

//	void OGLGraphicsRenderer::CreateProgram()
//	{
//		float verticies[] =
//		{
//			 0.5f,  0.5f,  0.0f,   1.0f, 1.0f, //front-top right
//			 0.5f, -0.5f,  0.0f,   1.0f, 0.0f, //front-bottom right
//			-0.5f, -0.5f,  0.0f,   0.0f, 0.0f, //front-bottom left
//			-0.5f,  0.5f,  0.0f,   0.0f, 1.0f //, //front-top left
//
//											 // 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  //back-top right
//											 // 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  //back-bottom right
//											 //-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  //back-bottom left
//											 //-0.5f,  0.5f, -0.5f,   0.0f, 1.0f   //back-top left
//
//		};
//
//		unsigned int indicies[] =
//		{
//			0, 1, 3,
//			1, 2, 3/*,
//
//				   4, 5, 7,
//				   5, 6, 7*/
//		};
//
//		BufferLayout bl;
//		bl.Add<float>("position", 0, 3, false);
//		bl.Add<float>("texCoord", 1, 2, false);
//
//		sh = Shader::Create();
//		sh->Init("Shaders/basic.glsl");
//
//		Material* mat = new Material();
//
//		//UniformDescription* desc = new UniformDescription();
//		//sh->Uniforms().AddUniform("modelColor", UniformDataType::COLOR);
//
//		mat->Uniforms().AddUniform("model", UniformDataType::MATRIX4);
//		mat->Uniforms().AddUniform("view", UniformDataType::MATRIX4);
//		mat->Uniforms().AddUniform("projection", UniformDataType::MATRIX4);
//
//		Matrix4 model(1.0f);
//		Matrix4 view(1.0f);
//		Matrix4 projection;
//
//		model *= Matrix4::Rotate(20.0f * DEGTORAD, Vector3(0.0f, 1.0f, 0.0f));
//		view *= Matrix4::Translate(Vector3(0.0f, 0.0f, -1.0f));
//		Vector2i size = engine->GetWindow()->GetSize();
//		projection = Matrix4::Perspective(45.0f * DEGTORAD, float(size.x / size.y), 0.1f, 100.0f);
//
//		mat->Uniforms().SetValueToUniform<Matrix4>("model", 1, &model);
//		mat->Uniforms().SetValueToUniform<Matrix4>("view", 1, &view);
//		mat->Uniforms().SetValueToUniform<Matrix4>("projection", 1, &projection);
//
//		mat->Uniforms().AddUniform("modelTexture", UniformDataType::INTEGER);
//		mat->Uniforms().AddUniform("modelTexture1", UniformDataType::INTEGER);
//		mat->Uniforms().SetValueToUniform<int>("modelTexture", 0);
//		mat->Uniforms().SetValueToUniform<int>("modelTexture1", 1);
//
//
////		mat->ResolveUniformLocations();
//
//
//
//		File imgFile = engine->GetFileSystem()->ReadFile("Resources/container.jpg");
//
//		Image img1(imgFile);
//
//		TextureParametrs params;
//
//		tex = Texture2D::Create(img1, params);
//
//		imgFile = engine->GetFileSystem()->ReadFile("Resources/awesomeface.png");
//
//		img1.Create(imgFile);
//		img1.FlipY();
//		img1.FlipX();
//
//		tex1 = Texture2D::Create(img1, params);
//
//		mesh.SetVertexBuffer(verticies, sizeof(verticies), BufferUsage::STATIC);
//		mesh.SetIndexBuffer(indicies, sizeof(indicies));
//	/*	mesh.SetBufferLayout(bl);
//
//		mesh.SetShader(sh);
//		mesh.AddTexture(tex1);
//		mesh.AddTexture(tex);*/
//
//		mesh.Initialize();
//	}
//
	void OGLGraphicsRenderer::Init(const Window& win)
	{
		GraphicsRenderer::Init(win);


		if (!gladLoadGL())
		{
			LOG("Failed to loat glad");
		}
		

		frameBufferWidth = size.x;
		frameBufferHeight = size.y;

		clearMask = 0;
		if (clearColorBuffer) clearMask |= GL_COLOR_BUFFER_BIT;
		if (clearDepthBuffer) clearMask |= GL_DEPTH_BUFFER_BIT;

		clearColor = Color(0.2f, 0.3f, 0.3f, 1.0f);

		frameBufferClearColor[0] = clearColor.NormalizedR();
		frameBufferClearColor[1] = clearColor.NormalizedG();
		frameBufferClearColor[2] = clearColor.NormalizedB();
		frameBufferClearColor[3] = clearColor.NormalizedA();
		//CreateProgram();
	}

	void OGLGraphicsRenderer::PreDraw()
	{
		BindFrameBuffer(frameBufferId);

		SetClearColorValue(frameBufferClearColor);
		SetViewport(0, 0, frameBufferWidth, frameBufferHeight);
		SetDepthMask(true);
		SetClearDepthValue(clearDepth);
		glCheck(glClear(clearMask));
	}

	void OGLGraphicsRenderer::Draw(DrawBatch* batch)
	{
		batch->material->Uniforms().SetValueToUniform<Matrix4>("projection", projection);
		batch->material->Uniforms().SetValueToUniform<Matrix4>("view", view);
		batch->material->Uniforms().SetValueToUniform<Matrix4>("model", batch->worldTransform->ToMatrix4());

		batch->material->Use();
		batch->mesh->Bind();

		glCheck(glDrawElements(GL_TRIANGLES, batch->mesh->GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr));
	}

	void OGLGraphicsRenderer::SetSize(const Vector2i& newSize)
	{
		GraphicsRenderer::SetSize(newSize);

		frameBufferWidth = newSize.x;
		frameBufferHeight = newSize.y;
	}

	void OGLGraphicsRenderer::SetClearColorBuffer(bool value)
	{
		GraphicsRenderer::SetClearColorBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_COLOR_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT);
	}

	void OGLGraphicsRenderer::SetClearDepthBuffer(bool value)
	{
		GraphicsRenderer::SetClearDepthBuffer(value);

		if (clearColorBuffer)
			clearMask |= GL_DEPTH_BUFFER_BIT;
		else
			clearMask &= static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT);
	}

	void OGLGraphicsRenderer::SetClearColor(const Color& color)
	{
		GraphicsRenderer::SetClearColor(color);

		frameBufferClearColor[0] = color.NormalizedR();
		frameBufferClearColor[1] = color.NormalizedG();
		frameBufferClearColor[2] = color.NormalizedB();
		frameBufferClearColor[3] = color.NormalizedA();
	}

	void OGLGraphicsRenderer::BindFrameBuffer(GLuint bufferId)
	{
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, bufferId));
	}

	void OGLGraphicsRenderer::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glCheck(glViewport(x, y, width, height));
	}

	void OGLGraphicsRenderer::SetClearColorValue(const float* clearColorValue)
	{
		glCheck(glClearColor(clearColorValue[0], clearColorValue[1], clearColorValue[2], clearColorValue[3]));
	}

	void OGLGraphicsRenderer::SetClearDepthValue(float clearDepthValue)
	{
		glCheck(glClearDepth(clearDepthValue));
	}

	void OGLGraphicsRenderer::SetDepthMask(bool value)
	{
		glCheck(glDepthMask(value ? GL_TRUE : GL_FALSE));
	}

}
