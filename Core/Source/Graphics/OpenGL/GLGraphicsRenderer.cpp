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

	Shader* sh;
	Texture2DResource* tex;
	Texture2DResource* tex1;
	Mesh mesh;

//	/*void OGLGraphicsRenderer::CreateProgram()
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
//	}*/

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
		//CreateProgram();

		
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

	void GLGraphicsRenderer::Draw(DrawBatch* batch)
	{
		batch->material->Uniforms().SetValueToUniform<Matrix4>("projection", frustum.GetMatrix());
		batch->material->Uniforms().SetValueToUniform<Matrix4>("view", camera.GetViewMatrix());
		batch->material->Uniforms().SetValueToUniform<Matrix4>("model", batch->worldTransform->ToMatrix4());

		batch->material->Use();
		batch->mesh->Bind();

		glCheck(glDrawElements(GL_TRIANGLES, batch->mesh->GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr));
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
