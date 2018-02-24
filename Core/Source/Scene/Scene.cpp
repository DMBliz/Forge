#include "Scene.h"

namespace Forge
{

	Scene::Scene()
	{
		
	}


	Scene::~Scene()
	{}

	void Scene::Update()
	{

		for (Entity* entity : childs)
		{
			entity->Update();
		}
	}
}
