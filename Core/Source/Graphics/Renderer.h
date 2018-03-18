#pragma once
#include "Context.h"
#include "GraphicsRenderer.h"
#include "RenderSurface.h"
#include "Model.h"
#include "Texture2D.h"

namespace Forge
{
	class Window;

	class Renderer
	{
	private:
		std::vector<Drawable*> drawables;
		GraphicsRenderer* deviceRenderer = nullptr;
	public:
		Renderer();
		~Renderer();

		void Init(const Vector2i& windowSize);
		void SetFrustum(const Frustum& frustum);
		const Frustum& GetFrustum() const;

		void AddDrawable(Drawable* drawable);

		virtual void Draw();

		//TODO: replace with custom(own) Vector
		bool RemoveDrawable(Drawable* drawable);

		bool ContainsDrawable(Drawable* drawable);

		Texture2D* GetScreenTexture() { return deviceRenderer->GetSurface()->GetColorTexture(); }

		void SetSize(const Vector2i& newSize);

		void SetWindowClearColor(const Color& color);
		const Color& GetWindowClearColor();

		void SetFrameBufferClearColor(const Color& color);
		const Color& GetFrameBufferClearColor();


		bool RenderToScreen() const
		{
			return deviceRenderer->RenderToScreen();
		}

		void RenderToScreen(bool value)
		{
			deviceRenderer->RenderToScreen(value);
		}

		void SetViewMatrix(const Matrix4& matrix) const 
		{
			deviceRenderer->GetCamera().SetMatrix(matrix);
		}
	};

}
