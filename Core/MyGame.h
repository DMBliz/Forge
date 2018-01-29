#pragma once
#include "Core/Game.h"
#include "Scene/Entity.h"

using namespace Forge;

class MyGame : public Game
{
private:
	Entity* spriteTest;
	Entity* spriteTest2;
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

