#pragma once

#include <memory>

#include "Layers/Layer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Render/Sprite.h"
#include "World/World.h"

class Actor;
class CC_Game;
class CC_KeyDownEvent;

class GameLayer : public Layer
{
    bool m_ShowWorldWindow = true;
    World* m_World = nullptr;
    
    Sprite* m_ActorSprite {};
    Actor* m_MainActor {};

    Sprite* m_EnemySprite {};
    Actor* m_EnemyActor {};

public:
    GameLayer();
    ~GameLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    // ImGUI
    
};
