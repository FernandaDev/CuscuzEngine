#pragma once

#include "EngineApplication.h"
#include "Game.h"

class Application : public EngineApplication
{
    std::unique_ptr<Game> m_Game;
    
public:
    Application() : m_Game(new Game()){}
    ~Application() override = default;

    void Start() override;
    void Update() override;
};
