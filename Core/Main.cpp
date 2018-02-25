#include "Core/Engine.h"
#include "Serialization/Serializers/JSON/JsonCast.h"
#include "EventSystem/Delegate.h"
#include "Serialization/Meta.h"
#include <fstream>
#include <thread>
#include "Graphics/OpenGL/GLGraphicsRenderer.h"
#include "Resources/Image.h"
#include "Scene/TransformComponent.h"
#include "Scene/SpriteRenderer.h"

using namespace Forge;
//nested serialize method with ISerializable




int main()
{
	Engine eng;
	eng.Init();
	eng.OpenWindow(Vector2i(800, 600), "Forge text", false, true);
	eng.Start();

	Entity* ent = eng.GetScene()->CreateEntity<Entity>();
	Component *tr = ent->AddComponent<TransformComponent>();
	Component *sp = ent->AddComponent<SpriteRenderer>();
	
	if(typeid(*tr) == typeid(TransformComponent))
	{
		std::cout << "works" << std::endl;
	}
	if(typeid(*sp) == typeid(SpriteRenderer))
	{
		std::cout << "works twice" << std::endl;
	}
	

	std::cin.get();
	return 0;
}