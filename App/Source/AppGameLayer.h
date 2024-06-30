#pragma once

#include "Layers/Layer.h"

class AppGame;
class Actor;
 class CC_Game;

 class AppGameLayer : public Layer
 {
     bool m_ShowDebugWindow;
     AppGame* m_AppGame;
     
 public:
     AppGameLayer(AppGame* appGame);
     ~AppGameLayer() override = default;

     void OnAttach() override;
     void OnDetach() override;
     void OnImGuiRender() override;
     void OnEvent(CC_Event& event) override;

 private:
    bool ToggleDebugWindow(const CC_KeyDownEvent& event);

    void ShowDebugWindow();
     
     void ActorCreation(bool showing) const;
     void ShowAllActors(bool showing) const;
     void ShowActor(Actor* actor, int index) const ;
 };
