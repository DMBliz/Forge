#pragma once
#include "Platform/Engine.h"

namespace Forge
{

	class WinEngine : public Engine
	{
	public:
		WinEngine();
		~WinEngine();

		void Init() override;

		void Start() override;

		void PlatrformUpdate() override;


		

	};

}
