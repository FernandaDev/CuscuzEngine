#pragma once

#include "AppImGuiLayer.h"
#include "Core/EngineApplication.h"
#include "Game.h"

class Application : public EngineApplication
{
    std::shared_ptr<Game> m_Game;
    
public:
    Application() : m_Game(std::make_shared<Game>(this)),
    CC_GUILayer(new AppImGuiLayer(*CC_Window,
                CC_RendererSystem->GetRenderer())) {}
    ~Application() override = default;

    void Start() override;
    void Update() override;

    AppImGuiLayer* CC_GUILayer;
protected:
    void Render() const override;
};
