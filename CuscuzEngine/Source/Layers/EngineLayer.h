#pragma once

#include "Layer.h"

enum class GameState
{
    Off = 0, Running = 1, Paused = 2
};

class EngineLayer : public Layer
{
    bool m_ShowPlayWindow = true;
    GameState m_GameState = GameState::Off;
    
public:
    EngineLayer() = default;
    ~EngineLayer() override = default;

    void OnAttach() override {}
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    bool TogglePlayWindow(const class CC_KeyDownEvent& event);
    void ShowPlayWindow();
};
