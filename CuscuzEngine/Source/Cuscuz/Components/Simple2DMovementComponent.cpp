﻿#include "pch.h"

#include "Simple2DMovementComponent.h"
#include "imgui.h"
#include "Cuscuz/Utils/Math.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    CREATE_COMPONENT_REGISTRY(Simple2DMovementComponent)

    Simple2DMovementComponent::Simple2DMovementComponent(float forwardSpeed, float angularSpeed, int updateOrder) :
        Component(updateOrder), m_ForwardSpeed(forwardSpeed), m_AngularSpeed(angularSpeed)
    {}

    void Simple2DMovementComponent::Update(float deltaTime)
    {
        Component::Update(deltaTime);

        if(!Math::NearZero(m_ForwardSpeed))
        {
            glm::vec3 position = m_OwnerActor->GetTransform().GetPosition();
            position += m_OwnerActor->GetTransform().GetForward() * m_ForwardSpeed * deltaTime;
            m_OwnerActor->GetTransform().SetPosition(position);
        }
    
        if(!Math::NearZero(m_AngularSpeed))
        {
            float rotation = m_OwnerActor->GetTransform().GetRotation();
            rotation += m_AngularSpeed * deltaTime;
            m_OwnerActor->GetTransform().SetRotation(rotation);
        }
    }

    void Simple2DMovementComponent::SetForwardSpeed(float speed)
    {
        m_ForwardSpeed = speed;
    }

    void Simple2DMovementComponent::SetAngularSpeed(float speed)
    {
        m_AngularSpeed = speed;
    }

    void Simple2DMovementComponent::ImGuiDisplayComponent()
    {
        ImGui::Dummy(ImVec2(0.0f, 3.0f));

        ImGui::Text("Forward Speed:");
        ImGui::SameLine();

        ImGui::DragFloat("##ForwardSpeed", &m_ForwardSpeed);

        ImGui::Text("Angular Speed:");
        ImGui::SameLine();

        ImGui::DragFloat("##AngularSpeed", &m_AngularSpeed);

        ImGui::Dummy(ImVec2(0.0f, 3.0f));
    }
}