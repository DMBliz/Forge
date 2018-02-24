#include "GLRenderSurface.h"
#include "Defines.h"
#include "glad/glad.h"
#include "GLCheck.h"

namespace Forge
{
	GLRenderSurface::~GLRenderSurface()
	{
		glCheck(glDeleteFramebuffers(1, &framebufferID));
	}

	void GLRenderSurface::Generate()
	{
		glCheck(glGenFramebuffers(1, &framebufferID));
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID));

		colorTexture->CreateOnGPU(size.x, size.y, TextureParametrs(TextureFilter::Linear, TextureWrap::Clamp_to_border, 
								  TextureInternalFormat::RGB, TextureFormat::RGB), false);

		glCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture->GetID(), 0));

		
		depthStencilTexture->CreateOnGPU(size.x, size.y, TextureParametrs(TextureFilter::Linear, TextureWrap::Clamp_to_border,
										 TextureInternalFormat::DepthStencil, TextureFormat::DepthStencil, 
										 TextureDataType::UnsignedInt_24_8), false);

		glCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTexture->GetID(), 0));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG("Can't initialize framebuffer");
		}

		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLRenderSurface::Bind()
	{
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID));
	}

	void GLRenderSurface::Resize(const Vector2i& newSize)
	{
		RenderSurface::Resize(newSize);
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID));
		colorTexture->SetTexture(nullptr, newSize);
		depthStencilTexture->SetTexture(nullptr, newSize);
		glCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}
