#include <CC_Engine.h>
#include "Game.h"

#include "Utils/Log.h"
#include "Application.h"
#include "World/World.h"
#include "World/Actor.h"
#include "Components/SpriteComponent.h"
#include "Components/Animation2DComponent.h"

Game::Game(Application* App):
m_GameIsRunning(false), m_World(new World), m_App(App)
{}

Game::~Game()
{
    ShutdownGame();
}

void Game::StartGame()
{
    m_GameIsRunning = true;
    
    const auto renderer = Application::Get().CC_RendererSystem->GetRenderer();

    Actor* actorA = CreateNewActor("ActorA", 230, 400);
    
    const auto animationComponent = new Animation2DComponent(4);
    actorA->AddComponent<Animation2DComponent>(animationComponent);
    
    const auto sprite = ResourceManager::Get().CreateSprite("player_tilesheet.png", renderer);
    animationComponent->SetSprite(sprite);

    Actor* actorB = CreateNewActor("ActorB",600, 500);
    
    const auto spriteComponent2 = new SpriteComponent( 10);
    actorB->AddComponent<SpriteComponent>(spriteComponent2);
    
    const auto sprite2 = ResourceManager::Get().CreateSprite("soldier.png", renderer);
    spriteComponent2->SetSprite(sprite2);
}

void Game::UpdateGame(float DeltaTime)
{
   m_World->Update(DeltaTime);
}

void Game::ShutdownGame()
{
    LOG_INFO("The game is shutting down...");
    m_GameIsRunning = false;
}

Actor* Game::CreateNewActor(const std::string& Name, int x, int y) const
{
    return new Actor(m_World, Name, glm::vec2(x,y));
}