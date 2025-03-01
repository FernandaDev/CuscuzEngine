#pragma once

#include <memory>

#include "Cuscuz/Core/Core.h"
#include "Cuscuz/Layers/Layer.h"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/World/World.h"

class Actor;
class CC_Game;
class CC_KeyDownEvent;

class GameLayer : public Cuscuz::Layer
{
    bool m_ShowWorldWindow = true;
    Cuscuz::World* m_World = nullptr;
    
    Cuscuz::CC_AssetRef<Cuscuz::Sprite> m_ActorSprite {};
    Actor* m_MainActor {};

public:
    GameLayer();
    ~GameLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(Cuscuz::CC_Event& event) override;
};
