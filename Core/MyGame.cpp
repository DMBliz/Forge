#include "MyGame.h"
#include "Scene/EntityManager.h"
#include "Scene/Entity.h"
#include "Scene/TransformComponent.h"
#include "Scene/SpriteRenderer.h"
#include "FileSystem/FileSystem.h"
#include "Resources/Image.h"
#include "Core/Engine.h"
#include "Utilities/Timer.h"
#include "Resources/Resources.h"
#include "Graphics/Texture2D.h"

MyGame::MyGame()
{}

MyGame::~MyGame()
{}

void MyGame::Initialize()
{
	Game::Initialize();
	engine->GetRenderer()->SetViewMatrix(Matrix4::Identity);
	engine->GetRenderer()->SetPerspectiveProjection(45.0f * DEGTORAD, 0.1f, 100.0f);
	/*Resources::RegisterResource<Texture2D>();
	Resources::RegisterResource<Image>();
	Resources::RegisterResource<Shader>();*/

	componentManager = new ComponentManager();
	entityManager = new EntityManager();
	
	entityManager->_componentManager = componentManager;
	
	spriteTest = entityManager->CreateEntity<Entity>();
	spriteTest2 = entityManager->CreateEntity<Entity>();
	spriteTest->AddComponent<TransformComponent>();
	spriteTest2->AddComponent<TransformComponent>();
	//TODO: make this work
	SpriteRenderer* rend = spriteTest->AddComponent<SpriteRenderer>();
	Texture2D* tex = Resources::Singleton()->LoadNowResource<Texture2D>("Resources/awesomeface.png");
	rend->SetTexture(tex);

	spriteTest->SetActive(true);
	rend->SetActive(true);

	tex = nullptr;
	tex = Resources::Singleton()->GetResource<Texture2D>("Resources/awesomeface.png");
	rend = spriteTest2->AddComponent<SpriteRenderer>();
	rend->SetTexture(tex);

	spriteTest2->SetActive(true);
	rend->SetActive(true);
}

void MyGame::Run()
{
	Game::Run();
}

void MyGame::Update()
{
	float ime = Timer::DeltaTime();
	if (engine->GetInputSystem()->KeyHold(KeyboardKey::D))
	{
		Vector3 pos = spriteTest->GetComponent<TransformComponent>()->Position();

		pos.x += 0.5f * Timer::DeltaTime();
		spriteTest->GetComponent<TransformComponent>()->Position(pos);
	}

	if (engine->GetInputSystem()->KeyHold(KeyboardKey::A))
	{
		Vector3 pos = spriteTest->GetComponent<TransformComponent>()->Position();
		pos.x -= 0.5f * Timer::DeltaTime();
		spriteTest->GetComponent<TransformComponent>()->Position(pos);
	}

	if (engine->GetInputSystem()->KeyHold(KeyboardKey::W))
	{
		Vector3 pos = spriteTest->GetComponent<TransformComponent>()->Position();

		pos.y += 0.5f * Timer::DeltaTime();
		spriteTest->GetComponent<TransformComponent>()->Position(pos);
	}

	if (engine->GetInputSystem()->KeyHold(KeyboardKey::S))
	{
		Vector3 pos = spriteTest->GetComponent<TransformComponent>()->Position();
		pos.y -= 0.5f * Timer::DeltaTime();
		spriteTest->GetComponent<TransformComponent>()->Position(pos);
	}

	if (engine->GetInputSystem()->KeyDown(KeyboardKey::Space))
	{
		Vector3 pos = spriteTest->GetComponent<TransformComponent>()->Position();
		pos.y += 50.5f * Timer::DeltaTime();
		spriteTest->GetComponent<TransformComponent>()->Position(pos);
	}
}

void MyGame::LoadContent()
{

}
