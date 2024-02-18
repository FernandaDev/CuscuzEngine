#include <CC_Engine.h>
#include "Game.h"

#include "Application.h"
#include "Utils/Log.h"
#include "World/Components/SpriteComponent.h"
#include "World/Actor.h"

Game::~Game()
{
    ShutdownGame();
}

void Game::StartGame()
{
    m_World = new World();
    m_GameIsRunning = true;
    
    Actor* actorA = new Actor(m_World, "ActorA", glm::vec2(230, 400), 2);

    const auto spriteComponent = new SpriteComponent(10);
    actorA->AddComponent<SpriteComponent>(spriteComponent);

    const auto renderer = Application::Get().CC_RendererSystem->GetRenderer();
    
    const auto sprite = ResourceManager::Get().CreateSprite("Floor1.png", renderer);
    spriteComponent->SetSprite(sprite);

    Actor* actorB = new Actor(m_World, "ActorB", glm::vec2(600, 500), 4);

    const auto spriteComponent2 = new SpriteComponent( 10);
    actorB->AddComponent<SpriteComponent>(spriteComponent2);

    const auto sprite2 = ResourceManager::Get().CreateSprite("Floor2.png", renderer);
    spriteComponent2->SetSprite(sprite2);
}

void Game::UpdateGame(float DeltaTime) const
{
    m_World->Update(DeltaTime);
}

void Game::ShutdownGame()
{
    LOG_INFO("The game is shutting down...");
    m_GameIsRunning = false;
    delete m_World;
}