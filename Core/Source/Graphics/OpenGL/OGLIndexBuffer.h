#pragma once
#include "Graphics/IndexBuffer.h"
#include "OGLGraphicsRenderer.h"

namespace Forge
{

	class OGLIndexBuffer : public IndexBuffer
	{
	private:
		uint bufferID = 0;
	public:
		OGLIndexBuffer(uint* data, uint count);
		~OGLIndexBuffer();
		
		void Generate() override;

		void Bind() override;
		void UnBind() override;

		uint GetCount() override;
	};

}
