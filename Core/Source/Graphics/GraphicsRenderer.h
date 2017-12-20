#pragma once
#include "Context.h"
#include "Math/Color.h"
#include "Math/Vector2i.h"
#include "Mesh.h"

namespace Forge
{
	class Material;
	class Window;

	class GraphicsRenderer
	{
		friend class Renderer;
	protected:
		ShaderUniforms* SystemUniform = nullptr;

		Color clearColor;
		float clearDepth = 1.0f;

		bool clearColorBuffer = true;
		bool clearDepthBuffer = true;

		Vector2i size;

		unsigned int sampleCount = 1;
		bool depth = false;
		bool debugRenderer = false;

		Context* context;
	public:
		GraphicsRenderer();
		virtual ~GraphicsRenderer();

		void SetSystemUniforms(ShaderUniforms* uniforms);
		virtual void Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer);

		virtual void PreDraw() = 0;
		virtual void Draw(Mesh* mesh, Material* material) = 0;
		virtual void PostDraw() = 0;

		virtual void SetSize(const Vector2i& newSize) { size = newSize; }
		const Vector2i& GetSize() { return size; }

		virtual void SetClearColorBuffer(bool value) { clearColorBuffer = value; }
		bool GetClearColorBuffer() { return clearColorBuffer; }

		virtual void SetClearDepthBuffer(bool value) { clearDepthBuffer = value; }
		bool GetClearDepthBuffer() { return clearDepthBuffer; }

		virtual void SetClearColor(const Color& color) { clearColor = color; }
		const Color& GetClearColor() { return clearColor; }

		virtual void SetClearDepth(float depth) { clearDepth = depth; }
		float GetClearDepth() { return clearDepth; }

		static GraphicsRenderer* Create();
	};

}
