#pragma once

#include <memory>
#include "Cuscuz.h"

namespace Cuscuz
{
    class CC_KeyDownEvent;

    class EditorLayer : public Layer
    {
        std::unique_ptr<OrthoCameraController> m_Camera;
        std::unique_ptr<World> m_EditorWorld;
        std::unique_ptr<Scene> m_EditorScene;

        CC_AssetRef<Sprite> m_ActorSprite {};
        CC_AssetRef<Texture2D> m_ActorTexture {};
        CC_AssetRef<Texture2D> m_Spritesheet {};
        std::array<CC_AssetRef<SubTexture2D>, 3> m_MapTiles;  // grass 5,29 | water 3,29 | dirt 6,29  
        Actor* m_MainActor {};

        bool m_ShowTimeStatsOverlay;
        bool m_IsViewportFocused = false;
        bool m_IsViewportHovered = false;
        float MoveSpeed = 1.f;

        glm::vec2 m_ViewportSize = {0, 0};
        CC_AssetRef<Framebuffer> m_Framebuffer;

    public:
        EditorLayer();
        ~EditorLayer() override = default;

        void OnAttach() override;

        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;
        void OnEvent(CuscuzEvent& event) override;

    private:
        void ShowEditorWindow();
        void DrawMenuBar();
        void DrawSceneWindow();
        void ShowHierarchyWindow(bool& show);

        void MoveActor(float deltaTime);
    };
}