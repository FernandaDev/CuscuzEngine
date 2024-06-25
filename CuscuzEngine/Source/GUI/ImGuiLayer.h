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
    ImGuiLayer(const Window& Window, SDL_Renderer* Renderer);
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnUpdate() override;
    
    void Render();

private:
    void OnSDLEvent(const SDL_Event& Event);

    void ShowMainWindow();
    void ToggleMainWindow(const CC_Event<CC_KeyEventType>& Event);

    void ActorCreation(CC_Game* Game, bool Showing) const;
    void ShowAllActors(CC_Game* Game, bool Showing) const;
    void ShowActor(Actor* TheActor, int Index) const ;
};
