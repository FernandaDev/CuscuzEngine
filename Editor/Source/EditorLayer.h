#pragma once

#include <memory>
#include "Cuscuz.h"

namespace Cuscuz
{
    class CC_KeyDownEvent;

    class EditorLayer : public Layer
    {
        std::unique_ptr<OrthoCameraController> m_CameraController;
        std::unique_ptr<World> m_EditorWorld;
        std::unique_ptr<Scene> m_EditorScene;

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
        void EditorWindowBegin();
        void DrawEditorWindow();
        void EditorWindowEnd();
        void DrawMenuBar();
        void DrawSceneWindow();
        void DrawHierarchyWindow(bool& show);
        void DrawInspectorWindow(bool& show);
        void DrawEditorCameraSettings(bool& show);

        bool OnKeyDownEvent(const CC_KeyDownEvent& event);
    };
}