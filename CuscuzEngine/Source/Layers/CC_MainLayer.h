#pragma once

#include "Layer.h"

enum class GameState
{
    Off = 0, Running = 1, Paused = 2
};

class CC_MainLayer : public Layer
{
    bool m_ShowPlayWindow = true;
    GameState m_GameState = GameState::Off;
    
public:
    CC_MainLayer() = default;
    ~CC_MainLayer() override = default;

    void OnAttach() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    bool TogglePlayWindow(const class CC_KeyDownEvent& event);
    void ShowPlayWindow();
};
