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

    Actor* actorA = new Actor(m_World, "ActorA");
    auto sc1 = actorA->AddComponent<SpriteComponent>(new SpriteComponent());
    
    const auto sprite1 = m_App->CC_RendererSystem->CreateSprite("Floor1.png", 250, 400);
    sc1.SetSprite(sprite1);
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