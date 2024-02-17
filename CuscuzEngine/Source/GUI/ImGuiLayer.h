#pragma once

#include "Core/Window.h"
#include "SDL.h"

class ImGuiLayer 
{
    SDL_Renderer& m_Renderer;
    
public:
    ImGuiLayer() = delete;
    ImGuiLayer(const Window& Window, 
               SDL_Renderer* Renderer);
    ~ImGuiLayer();

    void Start();
    void Update();
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);
};
