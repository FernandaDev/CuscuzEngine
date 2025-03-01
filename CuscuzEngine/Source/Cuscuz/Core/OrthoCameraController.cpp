#include "pch.h"
#include "OrthoCameraController.h"

#include "imgui.h"
#include "KeyCodes.h"
#include "Cuscuz/core/Input.h"
#include "Cuscuz/Events/CC_EventDispatcher.h"
#include "Cuscuz/Utils/Math.h"

namespace Cuscuz
{
    OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotate) :
        m_aspectRatio(aspectRatio), m_ZoomLevel(4.0f),
        m_Camera(-m_aspectRatio * m_ZoomLevel, m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
        m_CanRotate(rotate), m_Position(0), m_Rotation(0)
    {    }

    void OrthoCameraController::OnUpdate(float deltaTime)
    {
        if (Input::IsKeyPressed(CC_KeyCode::Up))
            m_Position.y += m_MovementSpeed * deltaTime;
        else if (Input::IsKeyPressed(CC_KeyCode::Down))
            m_Position.y -= m_MovementSpeed * deltaTime;

        if (Input::IsKeyPressed(CC_KeyCode::Right))
            m_Position.x += m_MovementSpeed * deltaTime;
        else if (Input::IsKeyPressed(CC_KeyCode::Left))
            m_Position.x -= m_MovementSpeed * deltaTime;

        m_Camera.SetPosition(m_Position);
        m_MovementSpeed = m_ZoomLevel;

        if (!m_CanRotate)
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
        SetZoomLevel(m_ZoomLevel - event.GetY() * m_ZoomStep);

        return false;
    }

    bool OrthoCameraController::OnWindowResized(CC_WindowResizeEvent& event)
    {
        m_aspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
        m_Camera.SetProjection(-m_aspectRatio * m_ZoomLevel, m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

    void OrthoCameraController::SetZoomLevel(float amount)
    {
        m_ZoomLevel = amount;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_aspectRatio * m_ZoomLevel, m_aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    void OrthoCameraController::OnImGuiRender()
    {
        ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Camera");

        ImGui::Separator();

        ImGui::PushItemWidth(100.0f);

        ImGui::Text("Position");

        auto pos = m_Position;

        ImGui::DragFloat("x##pos", &pos.x);
        ImGui::SameLine();
        ImGui::DragFloat("y##pos", &pos.y);

        m_Camera.SetPosition(pos);

        ImGui::Dummy(ImVec2(0.0f, 3.0f));

        ImGui::Text("Rotation");

        auto rot = m_Rotation;

        ImGui::DragFloat("degrees", &rot);

        m_Camera.SetRotation(rot);

        ImGui::Separator();

        ImGui::Text("Aspect Ratio:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "%.1f", m_aspectRatio);

        ImGui::Dummy(ImVec2(0.0f, 1.0f));

        ImGui::Text("Zoom Level:");
        ImGui::SameLine();
        auto zoomLevel = m_ZoomLevel;
        ImGui::DragFloat("##ZoomLevel", &zoomLevel, 1.f, MaxZoomAmount);
        if (!FLOAT_EQUAL(zoomLevel, m_ZoomLevel))
            SetZoomLevel(zoomLevel);

        ImGui::Dummy(ImVec2(0.0f, 1.0f));

        ImGui::Text("Zoom Step:");
        ImGui::SameLine();
        ImGui::DragFloat("##ZoomStep", &m_ZoomStep, 1.f, 0);

        ImGui::Dummy(ImVec2(0.0f, 1.0f));
    }
}
