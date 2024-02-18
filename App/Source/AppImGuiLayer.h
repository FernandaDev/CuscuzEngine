#pragma once

#include "Game.h"
#include "SDL.h"

class Window;

class AppImGuiLayer
{
    SDL_Renderer* m_Renderer;
    std::weak_ptr<Game> m_Game;

    bool m_ShowMainWindow;
    
public:
    AppImGuiLayer(const Window& Window, SDL_Renderer* Renderer);
    ~AppImGuiLayer();
    
    void Start(const std::weak_ptr<Game>& Game);
    void Update();
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);

    void ShowMainWindow();
};
