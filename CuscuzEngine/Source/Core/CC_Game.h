#pragma once
#include "World/World.h"

class EngineApplication;
class Actor;

class CC_Game
{
    bool m_GameIsPaused;
    friend class ImGuiLayer;

protected:
    bool m_GameIsRunning;
    World m_World;
    
public:
    CC_Game();
    virtual ~CC_Game() = default;
    
    virtual void OnGameBegin(){}
    virtual void OnGameEnd(){}
    virtual void UpdateGame(float DeltaTime);

    bool IsRunning() const { return m_GameIsRunning; }
    void StartGame();
    void ShutdownGame();

private:
    void PauseGame();

    friend class EngineAppLayer;
};
