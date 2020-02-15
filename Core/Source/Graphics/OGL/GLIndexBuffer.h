#pragma once
#include "Graphics/IndexBuffer.h"
#include "GLGraphicsRenderer.h"

namespace Forge
{

	class GLIndexBuffer : public IndexBuffer
	{
	private:
		uint bufferID = 0;
	public:
		GLIndexBuffer(uint* data, uint count);
		~GLIndexBuffer();
		
		void Generate() override;

		void Bind() override;
		void UnBind() override;

		uint GetCount() override;
	};

}
