#include "Model.h"
#include "Core/Engine.h"

namespace Forge
{

	Model::Model()
	{}

	Model::~Model()
	{}

	void Model::EnableDrawing()
	{
		for(int i = 0; i < _batches.size(); i++)
		{
			engine->GetRenderer()->AddDrawBatch(_batches[i]);
		}
	}

	void Model::DisableDrawing()
	{
		for (int i = 0; i < _batches.size(); i++)
		{
			engine->GetRenderer()->RemoveDrawBatch(_batches[i]);
		}
	}
}
