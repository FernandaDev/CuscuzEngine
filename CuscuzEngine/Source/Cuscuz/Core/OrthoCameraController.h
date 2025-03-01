#pragma once

#include "Cuscuz/Render/Camera.h"
#include "Cuscuz/Events/WindowEvents.h"
#include "Cuscuz/Events/MouseEvents.h"

namespace Cuscuz
{
    class OrthoCameraController
    {
        float m_aspectRatio;
        float m_ZoomLevel;
        OrthographicCamera m_Camera;

        bool m_CanRotate;
        glm::vec3 m_Position;
        float m_Rotation;
        float m_MovementSpeed = 20.f;
        float m_RotationSpeed = 180.f;
        float m_ZoomStep = .5f;

        const float MaxZoomAmount = 0.25f;

    public:
        OrthoCameraController(float aspectRatio, bool rotate = false);

        void OnUpdate(float deltaTime);
        void OnEvent(CC_Event& event);
        void OnImGuiRender();

        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(CC_MouseScrolledEvent& event);
        bool OnWindowResized(CC_WindowResizeEvent& event);

        void SetZoomLevel(float amount);
    };
}
