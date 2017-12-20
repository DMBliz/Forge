#pragma once
#include "Game.h"
#include "EntityComponent/Entity.h"

using namespace Forge;

class MyGame : public Game
{
private:
	Entity* spriteTest;
	EntityManager* entityManager;
	ComponentManager* componentManager;
public:
	MyGame();
	~MyGame();

	void Initialize() override;
	void Run() override;
	void Update() override;
	void LoadContent() override;
};

