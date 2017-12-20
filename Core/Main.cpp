#include <iostream>
#include "Math/Mathf.h"
#include "Platform/Engine.h"
#include "MyGame.h"

using namespace Forge;
int main()
{
	Engine eng;
	Game* myGame = new MyGame();
	eng.OpenWindow(Vector2i(800, 600), "Forge text", false, true);
	eng.SetGame(myGame);
	eng.Start();

	return 0;
}