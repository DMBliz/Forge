#pragma once
#include "Context.h"
#include "GraphicsRenderer.h"
#include "Model.h"

namespace Forge
{
	class Window;

	class Renderer
	{
	private:
		std::vector<DrawBatch*> drawBatches;
		GraphicsRenderer* deviceRenderer;
	public:
		
		void Init(Window* win);
		void SetProjectionMatrix(const Matrix4& projection);
		void SetPerspectiveProjection(float fov, float near, float far);
		void SetOrthographicProjection(float near, float far);
		void SetViewMatrix(const Matrix4& view);

		void AddDrawBatch(DrawBatch* drawBatch)
		{
			drawBatches.push_back(drawBatch);
		}

		virtual void Draw()
		{
			deviceRenderer->PreDraw();

			for (uint i = 0; i < drawBatches.size(); i++)
			{
				deviceRenderer->Draw(drawBatches[i]);
			}
		}

		//TODO: replace with custom(own) Vector
		bool RemoveDrawBatch(DrawBatch* drawBatch)
		{
			if (ContainsDrawBatch(drawBatch))
			{
				auto it = std::find(drawBatches.begin(), drawBatches.end(), drawBatch);
				drawBatches.erase(it);
				return true;
			}

			return false;
		}

		bool ContainsDrawBatch(DrawBatch* drawBatch)
		{
			return std::find(drawBatches.begin(), drawBatches.end(), drawBatch) != drawBatches.end();
		}

		Renderer();
		~Renderer();
	};

}
