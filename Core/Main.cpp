#include "Core/Engine.h"

int main()
{
    Forge::Engine eng;
    Forge::Application* app = Forge::getApplication();

	eng.Init(app);

	eng.Start();

	return 0;
}