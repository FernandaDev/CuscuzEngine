#include "Game.h"

#include "Utils/Log.h"
#include "World/World.h"

Game::~Game()
{
    ShutdownGame();
}

void Game::StartGame()
{
    m_World = new World();
    m_GameIsRunning = true;

    Actor* actorA = new Actor(m_World, "ActorA");
    Actor* actorB = new Actor(m_World, "ActorB");
    Actor* actorC = new Actor(m_World, "ActorC");
}

void Game::UpdateGame(float DeltaTime) const
{
    //m_World->Update(DeltaTime);
}

void Game::ShutdownGame()
{
    LOG_INFO("The game is shutting down...");
    m_GameIsRunning = false;
    delete m_World;
}