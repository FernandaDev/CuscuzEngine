#include "pch.h"
#include "OrthoCameraController.h"

#include "KeyCodes.h"
#include "core/Input.h"
#include "Events/CC_EventDispatcher.h"

OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotate) :
m_aspectRatio(aspectRatio), m_ZoomLevel(100.0f),
m_Camera(-m_aspectRatio * m_ZoomLevel,m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
m_CanRotate(rotate), m_Position(0), m_Rotation(0)
{ }

void OrthoCameraController::OnUpdate(float deltaTime)
{
    if(Input::IsKeyPressed(CC_KeyCode::Up))
        m_Position.y += m_MovementSpeed * deltaTime;
    else if(Input::IsKeyPressed(CC_KeyCode::Down))
        m_Position.y -= m_MovementSpeed * deltaTime;

    if(Input::IsKeyPressed(CC_KeyCode::Right))
        m_Position.x += m_MovementSpeed * deltaTime;
    else if(Input::IsKeyPressed(CC_KeyCode::Left))
        m_Position.x -= m_MovementSpeed * deltaTime;
        
    m_Camera.SetPosition(m_Position);
    m_MovementSpeed = m_ZoomLevel;

    if(!m_CanRotate)
        return;

    if (Input::IsKeyPressed(CC_KeyCode::RCtrl))
        m_Rotation -= m_RotationSpeed * deltaTime;
    else if (Input::IsKeyPressed(CC_KeyCode::RShift))
        m_Rotation += m_RotationSpeed * deltaTime;

    m_Camera.SetRotation(m_Rotation);
}

void OrthoCameraController::OnEvent(CC_Event& event)
{
    CC_EventSingleDispatcher dispatcher(event);
    dispatcher.Dispatch<CC_MouseScrolledEvent>(BIND_FUNCTION(this, OrthoCameraController::OnMouseScrolled));
    dispatcher.Dispatch<CC_WindowResizeEvent>(BIND_FUNCTION(this, OrthoCameraController::OnWindowResized));
}

bool OrthoCameraController::OnMouseScrolled(CC_MouseScrolledEvent& event)
{
    m_ZoomLevel -= event.GetY() * m_ZoomStep;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjection(-m_aspectRatio * m_ZoomLevel,m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    
    return false;
}

bool OrthoCameraController::OnWindowResized(CC_WindowResizeEvent& event)
{
    m_aspectRatio -= static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
    m_Camera.SetProjection(-m_aspectRatio * m_ZoomLevel,m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    
    return false;
}
