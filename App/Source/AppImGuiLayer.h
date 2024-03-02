#pragma once

#include "SDL.h"

class Game;
class Window;
class Actor;

class AppImGuiLayer
{
    SDL_Renderer* m_Renderer;
    std::weak_ptr<Game> m_Game;

    bool m_ShowMainWindow;
    
public:
    AppImGuiLayer(const Window& Window, SDL_Renderer* Renderer);
    ~AppImGuiLayer();
    
    void Start(const std::shared_ptr<Game>& Game);
    void Update();
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);

    void ShowMainWindow();

    void ActorCreation(const std::shared_ptr<Game>& Game, bool Showing) const;
    void ShowAllActors(const std::shared_ptr<Game>& Game, bool Showing) const;
    void ShowActor(Actor* TheActor, int Index) const ;
};
