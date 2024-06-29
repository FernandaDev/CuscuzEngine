﻿#pragma once

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
    ImGuiLayer(const Window& window, SDL_Renderer* renderer);
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnUpdate() override;
    void OnEvent(CC_Event& event) override;
    
    //void Render();

private:
    bool OnSDLEvent(const class CC_SDLEvent& event);
    bool ToggleMainWindow(const CC_KeyDownEvent& event);

    void ShowMainWindow();
    void ActorCreation(CC_Game* game, bool showing) const;
    void ShowAllActors(CC_Game* game, bool showing) const;
    void ShowActor(Actor* theActor, int index) const ;
};