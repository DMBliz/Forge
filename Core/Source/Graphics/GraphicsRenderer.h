#pragma once
#include "Context.h"
#include "Math/Color.h"
#include "Math/Vector2i.h"
#include "Mesh.h"
#include "Drawable.h"

namespace Forge
{
	class Material;
	class Window;

	class GraphicsRenderer
	{
		friend class Renderer;
	protected:
		Color clearColor;
		float clearDepth = 1.0f;

		bool clearColorBuffer = true;
		bool clearDepthBuffer = true;

		Vector2i size;

		unsigned int sampleCount = 1;
		bool depth = false;
		bool debugRenderer = false;

		Matrix4 projection;
		Matrix4 view;
	public:
		GraphicsRenderer();
		virtual ~GraphicsRenderer();

		virtual void Init(const Window& win);

		virtual void PreDraw() = 0;
		virtual void Draw(DrawBatch* batch) = 0;

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

		void SetProjection(const Matrix4& matrix)
		{
			projection = matrix;
		}

		void SetView(const Matrix4& matrix)
		{
			view = matrix;
		}

		static GraphicsRenderer* Create();
	};

}
