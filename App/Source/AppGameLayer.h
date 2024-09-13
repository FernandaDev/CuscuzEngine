#pragma once

#include "Layers/Layer.h"

class AppGame;
class Actor;
class CC_Game;
class CC_KeyDownEvent;

 class AppGameLayer : public Layer
 {
     bool m_ShowWorldWindow;
     std::shared_ptr<AppGame> m_AppGame;
     
 public:
     AppGameLayer(const std::shared_ptr<AppGame>& appGame);
     ~AppGameLayer() override = default;

     void OnAttach() override;
     void OnDetach() override;
     void OnImGuiRender() override;
     void OnEvent(CC_Event& event) override;

 private:
    bool ToggleWindow(const CC_KeyDownEvent& event);

    void ShowWorldWindow();
     
     void ActorCreation(bool showing) const;
     void ShowAllActors(bool showing) const;

     void ShowActor(Actor* actor, int index) const ;
     void ShowActorComponents(Actor* actor, int index) const;
 };
