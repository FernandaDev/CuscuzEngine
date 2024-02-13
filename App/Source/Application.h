#pragma once

#include "EngineApplication.h"
#include "Game.h"

class Application : public EngineApplication
{
    std::unique_ptr<Game> m_Game;
    
public:
    Application() : m_Game(std::make_unique<Game>(this)){}
    ~Application() override = default;
    
private:

    void Start() override;
    void Update() override;
};
