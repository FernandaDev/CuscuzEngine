#pragma once

#include "Layer.h"

class CC_Game;
class EventSystem;
class RendererSystem;

class EngineAppLayer : public Layer
{
    EventSystem* m_EventSystem;
    RendererSystem* m_RendererSystem;
    CC_Game* m_Game;

    bool m_ShowPlayWindow;
    
public:
    EngineAppLayer(EventSystem* eventSystem, RendererSystem* renderer, CC_Game* game);

    void OnUpdate() override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    bool ToggleMainWindow(const class CC_KeyDownEvent& event);
    void ShowPlayWindow();
};
