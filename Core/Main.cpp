#include "Core/Engine.h"
#include "MyGame.h"
#include "Serialization/Serializers/JSON/JsonCast.h"
#include "EventSystem/Delegate.h"
#include "Serialization/Meta.h"
#include <fstream>
#include <thread>
#include "Graphics/OpenGL/OGLGraphicsRenderer.h"
#include "Resources/Image.h"

using namespace Forge;

int main()
{
	Engine eng;
	Game* myGame = new MyGame();
	eng.OpenWindow(Vector2i(800, 600), "Forge text", false, true);
	eng.SetGame(myGame);
	eng.Start();

	std::cin.get();
	return 0;
}