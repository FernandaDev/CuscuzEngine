#pragma once

#include <memory>

#include "Cuscuz.h"

class CC_KeyDownEvent;

class EditorLayer : public Cuscuz::Layer
{
    std::unique_ptr<Cuscuz::OrthoCameraController> m_Camera;
    std::unique_ptr<Cuscuz::World> m_EditorWorld;
    std::unique_ptr<Cuscuz::Scene> m_EditorScene;

    Cuscuz::CC_AssetRef<Cuscuz::Sprite> m_ActorSprite {};
    Cuscuz::CC_AssetRef<Cuscuz::Texture2D> m_ActorTexture {};
    Cuscuz::Actor* m_MainActor {};

    bool m_ShowWorldWindow;
    bool m_ShowTimeStatsOverlay;

    float MoveSpeed = 1.f;

public:
    EditorLayer();
    ~EditorLayer() override = default;

    void OnAttach() override;

    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(Cuscuz::CuscuzEvent& event) override;

private:
    void MoveActor(float deltaTime);
    bool ToggleWindow(const CC_KeyDownEvent& event);
    void ShowWorldWindow();
};
