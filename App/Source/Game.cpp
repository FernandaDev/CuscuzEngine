﻿#include <CC_Engine.h>
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
    
    Actor* actorA = new Actor(m_World, "ActorA", glm::vec2(230, 400));

    //the sprite component is only created by the renderer system
    const auto spriteComponent = new SpriteComponent(glm::vec2(1,1), 10);
    actorA->AddComponent<SpriteComponent>(spriteComponent);

    const auto renderer = Application::Get().CC_RendererSystem->GetRenderer();
    
    const auto sprite = ResourceManager::Get().CreateSprite("Floor1.png", renderer);
    spriteComponent->SetSprite(sprite);
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