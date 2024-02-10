#pragma once

class World;

class Game
{
    bool m_GameIsRunning = false;
    World* m_World;
    
public:
    Game() = default;
    ~Game();
    
    void StartGame();
    void UpdateGame(float DeltaTime) const;
    void ShutdownGame();

    bool IsRunning() const { return m_GameIsRunning; }
};
