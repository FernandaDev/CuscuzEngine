#include "pch.h"
#include "CC_Game.h"
#include "../World/World.h"

CC_Game::CC_Game() :
    m_GameIsPaused(false), m_GameIsRunning(false)
{}

void CC_Game::StartGame()
{
    m_GameIsRunning = true;
    OnGameBegin();
}

void CC_Game::PauseGame()
{
    m_GameIsPaused = !m_GameIsPaused;
}

void CC_Game::UpdateGame(float deltaTime)
{
    if(m_GameIsPaused)
        return;
    
    m_World.Update(deltaTime);
}

void CC_Game::ShutdownGame()
{
    m_World.ResetWorld();
    m_GameIsRunning = false;
    m_GameIsPaused = false;
    OnGameEnd();
}
