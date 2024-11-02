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
    std::unique_ptr<World> m_World {};

    std::shared_ptr<OpenGLTexture> m_ActorTexture {};
    std::shared_ptr<Sprite> m_ActorSprite {};

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
    bool ToggleWindow(const CC_KeyDownEvent& event);
    void ShowWorldWindow();
};
