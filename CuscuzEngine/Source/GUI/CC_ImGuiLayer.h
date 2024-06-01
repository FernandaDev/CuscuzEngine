#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"
#include "Events/KeyEvents.h"

class Actor;
class Window;
class CC_Game;

class CC_ImGuiLayer
{
    bool m_ShowMainWindow;
    
public:
    CC_ImGuiLayer(const Window& Window, SDL_Renderer* Renderer);
    ~CC_ImGuiLayer();

    void Init();
    void Update();
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);

    void ShowMainWindow();
    void ToggleMainWindow(const CC_Event<CC_KeyEventType>& Event);

    void ActorCreation(CC_Game* Game, bool Showing) const;
    void ShowAllActors(CC_Game* Game, bool Showing) const;
    void ShowActor(Actor* TheActor, int Index) const ;
};
