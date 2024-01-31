#pragma once

#include "imgui.h"
#include "Window.h"
#include "SDL.h"
#include "Events/CC_Event.h"
#include "Events/MouseEvents.h"

class ImGuiLayer 
{
    bool m_ShowDemoWindow;
    bool m_ShowAnotherWindow;
    ImVec4 m_ClearColor;

    SDL_Renderer& m_Renderer;
    
public:
    ImGuiLayer() = delete;
    ImGuiLayer(const Window& Window, 
               SDL_Renderer* Renderer);
    ~ImGuiLayer();

    void Update();
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);
    void OnMouseMove(const CC_Event<CC_MouseEventType>& MouseEvent);
    void OnMouseButtonUp(const CC_Event<CC_MouseEventType>& MouseEvent);
    void OnMouseButtonDown(const CC_Event<CC_MouseEventType>& MouseEvent);
};
