#pragma once
#include "Context.h"
#include "GraphicsRenderer.h"
#include "RenderSurface.h"
#include "Model.h"
#include "Texture2D.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

namespace Forge
{
	class Window;

    struct DrawCommand
    {
        Mesh* _mesh;
        Material* _material;

        bool transparent = false;
        Matrix4 worldTransform;
    };

	class Renderer
	{
	private:
		std::vector<DrawCommand> _drawBuffer;

        std::map<float, DrawCommand> _transparentBuffer;

        std::vector<DirectionalLight*> _dirLights;
        std::vector<PointLight*> _pointLights;
        std::vector<SpotLight*> _spotLights;

        int _maxDirLights = 2;
        int _maxPointLights = 127;
        int _maxSpotLights = 127;

        Frustum _frustum;
        Camera _camera;
		GraphicsRenderer* _deviceRenderer = nullptr;
	public:
		Renderer();
		~Renderer();

		void Init(const Vector2i& windowSize);
		void SetFrustum(const Frustum& frustum);
		const Frustum& GetFrustum() const;

		void PushCommand(DrawCommand command);

        void AddLight(DirectionalLight* light);
        void AddLight(PointLight* light);
        void AddLight(SpotLight* light);
        void RemoveLight(DirectionalLight* light);
        void RemoveLight(PointLight* light);
        void RemoveLight(SpotLight* light);

		virtual void Draw();

        const std::vector<DirectionalLight*>& GetDirLights() const;
        const std::vector<PointLight*>& GetPointLights() const;
        const std::vector<SpotLight*>& GetSpotLights() const;

		Texture2D* GetScreenTexture() { return _deviceRenderer->GetSurface()->GetColorTexture(); }

		void SetSize(const Vector2i& newSize);

		void SetWindowClearColor(const Color& color);
		const Color& GetWindowClearColor();

		void SetFrameBufferClearColor(const Color& color);
		const Color& GetFrameBufferClearColor();


		bool RenderToScreen() const
		{
			return _deviceRenderer->RenderToScreen();
		}

		void RenderToScreen(bool value)
		{
			_deviceRenderer->RenderToScreen(value);
		}

		void SetViewMatrix(const Matrix4& matrix) 
		{
			_camera.SetMatrix(matrix);
		}

        Camera& GetCamera()
		{
            return _camera;
		}
	};

}
