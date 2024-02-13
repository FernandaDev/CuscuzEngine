#pragma once

#include "World/World.h"

class Application;

class Game
{
    bool m_GameIsRunning;
    World* m_World;
    Application* m_App;
    
public:
    Game(Application* App) :
    m_GameIsRunning(false), m_World(nullptr), m_App(App)
    {}
    ~Game();
    
    void StartGame();
    void UpdateGame(float DeltaTime) const;
    void ShutdownGame();

    bool IsRunning() const { return m_GameIsRunning; }
};
