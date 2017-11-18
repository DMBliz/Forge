#include <iostream>
#include "Math/Mathf.h"
#include "Platform/Windows/WinEngine.h"

using namespace Forge;
int main()
{
	WinEngine eng;
	eng.Init();
	eng.Start();
	eng.Update();

	return 0;
}