#include "MyGame.h"
#include "EntityComponent/TransformComponent.h"
#include "EntityComponent/EntityManager.h"
#include "EntityComponent/SpriteRenderer.h"
#include "FileSystem/FileSystem.h"
#include "Graphics/Image.h"

MyGame::MyGame()
{}


MyGame::~MyGame()
{}

void MyGame::Initialize()
{
	Game::Initialize();
	componentManager = new ComponentManager();
	entityManager = new EntityManager();
	
	entityManager->_componentManager = componentManager;
	
	spriteTest = entityManager->CreateEntity<Entity>();
	spriteTest->AddComponent<TransformComponent>();
	spriteTest->AddComponent<SpriteRenderer>();
	SpriteRenderer* rend = spriteTest->GetComponent<SpriteRenderer>();
	Image* img = new Image(FileSystem::ReadFile("Resources/awesomeface.png"));
	Texture2D* tex = Texture2D::Create(*img, TextureParametrs());
	rend->SetTexture(tex);

	spriteTest->SetActive(true);
	rend->SetActive(true);
}

void MyGame::Run()
{
	Game::Run();
}

void MyGame::Update()
{

}

void MyGame::LoadContent()
{

}
