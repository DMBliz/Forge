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

		static Renderer* GetRenderer()
		{
			Renderer* rend = new Renderer();
			return rend;
		}
		
		virtual void Init(Window* win);

		void AddDrawBatch(DrawBatch* drawBatch)
		{
			drawBatches.push_back(drawBatch);
		}

		virtual void Draw()
		{
			deviceRenderer->PreDraw();

			for (int i = 0; i < drawBatches.size(); i++)
			{
				deviceRenderer->Draw(drawBatches[i]->mesh, drawBatches[i]->material);
			}

			deviceRenderer->PostDraw();
		}

		//TODO: replace with custom Vector
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

		void SetSystemUniforms(ShaderUniforms* uniforms)
		{
			deviceRenderer->SetSystemUniforms(uniforms);
		}

		ShaderUniforms* GetSystemUniforms()
		{
			return deviceRenderer->SystemUniform;
		}

		Renderer();
		~Renderer();
	};

}
