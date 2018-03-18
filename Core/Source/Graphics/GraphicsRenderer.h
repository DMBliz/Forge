#pragma once
#include "Math/Color.h"
#include "Math/Vector2i.h"
#include "Drawable.h"
#include "Math/Frustum.h"
#include "Camera.h"

namespace Forge
{
	class RenderSurface;
	class Material;
	class Window;
	class Mesh;

	class GraphicsRenderer
	{
		friend class Renderer;
	protected:
		void SetupScreenPresenter();
		Mesh screenMesh;
		Material screenMaterial;
		RenderSurface* renderSurface;

		Color clearColor;
		float clearDepth = 1.0f;

		bool clearColorBuffer = true;
		bool clearDepthBuffer = true;

		Vector2i size;

		unsigned int sampleCount = 1;
		bool depth = true;
		bool debugRenderer = false;

		bool renderToScreen = true;

		Frustum frustum;
		Camera camera;

	public:
		GraphicsRenderer();
		virtual ~GraphicsRenderer();

		virtual void Init(const Vector2i& windowSize) = 0;

		virtual void PreDraw() = 0;
		virtual void Draw(Drawable* drawable) = 0;
		virtual void PostDraw() = 0;

		virtual void DrawToScreen() = 0;

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

		void SetFrustum(const Frustum& newFrustum)
		{
			frustum = newFrustum;
		}

		Frustum& GetFrustum()
		{
			return frustum;
		}

		Camera& GetCamera()
		{
			return camera;
		}

		RenderSurface* GetSurface() const { return renderSurface; }


		bool RenderToScreen() const
		{
			return renderToScreen;
		}

		void RenderToScreen(bool value)
		{
			renderToScreen = value;
		}

		static GraphicsRenderer* Create();
	};

}
