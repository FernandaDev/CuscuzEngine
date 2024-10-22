#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"
#include "Events/KeyEvents.h"
#include "Layers/Layer.h"

class Actor;
class Window;
class CC_Game;

class ImGuiLayer : public Layer
{
    bool m_ShowMainWindow;
    
public:
    ImGuiLayer(const Window& window);
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

    void Begin();
    void End();

private:
    bool OnSDLEvent(const class CC_SDLEvent& event);
    bool ToggleMainWindow(const CC_KeyDownEvent& event);

    void ShowMainWindow();

};
