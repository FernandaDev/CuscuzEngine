#pragma once

#include <memory>
#include "Cuscuz.h"

class CC_Game;
class CC_KeyDownEvent;

class GameLayer : public Cuscuz::Layer
{
    bool m_ShowWorldWindow = true;
    std::unique_ptr<Cuscuz::World> m_World {};
    Cuscuz::CC_AssetRef<Cuscuz::Sprite> m_ActorSprite {};
    Cuscuz::Actor* m_MainActor {};

public:
    GameLayer();
    ~GameLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(Cuscuz::CuscuzEvent& event) override;
};
