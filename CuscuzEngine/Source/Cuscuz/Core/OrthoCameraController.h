#pragma once

#include "Cuscuz/Render/Camera.h"
#include "Cuscuz/Events/WindowEvents.h"
#include "Cuscuz/Events/MouseEvents.h"

namespace Cuscuz
{
    struct OrthographicCameraBounds
    {
        float Left, Right;
        float Bottom, Top;

        OrthographicCameraBounds(float left, float right,float bottom, float top):
        Left(left), Right(right), Bottom(bottom), Top(top) { }
        
        float GetWidth() const { return Right - Left; }
        float GetHeight() const { return Top - Bottom; }
    };
    
    class OrthoCameraController
    {
        float m_aspectRatio;
        float m_ZoomLevel;
        OrthographicCameraBounds m_Bounds;
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
        void OnEvent(CuscuzEvent& event);
        void OnImGuiRender();

        const OrthographicCamera& GetCamera() const { return m_Camera; }
        const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

    private:
        bool OnMouseScrolled(CC_MouseScrolledEvent& event);
        bool OnWindowResized(CC_WindowResizeEvent& event);

        void SetZoomLevel(float amount);
    };
}
