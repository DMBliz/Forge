#pragma once

namespace Forge
{

	class Game
	{
	public:
		Game();
		~Game();

		virtual void Initialize();
		virtual void Run();
		virtual void Update();
		virtual void LoadContent();
	};

}
