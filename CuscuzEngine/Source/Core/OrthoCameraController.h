#pragma once

#include "Render/Camera.h"
#include "Events/WindowEvents.h"
#include "Events/MouseEvents.h"

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
    float m_ZoomStep = 10.f;
    
public:
    OrthoCameraController(float aspectRatio, bool rotate = false);

    void OnUpdate(float deltaTime);
    void OnEvent(CC_Event& event);

    const OrthographicCamera& GetCamera() const { return m_Camera; }
    
private:
    bool OnMouseScrolled(CC_MouseScrolledEvent& event);
    bool OnWindowResized(CC_WindowResizeEvent& event);
};
