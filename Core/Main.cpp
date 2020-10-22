#include "Core/Engine.h"

int main()
{
    Forge::Engine eng;
    Forge::Application* app = Forge::getApplication();

	eng.init(app);

	eng.start();

	return 0;
}