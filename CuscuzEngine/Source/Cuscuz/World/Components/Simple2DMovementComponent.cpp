#include "pch.h"

#include "Simple2DMovementComponent.h"
#include "imgui.h"
#include "Cuscuz/Utils/Math.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    Simple2DMovementComponent::Simple2DMovementComponent(const glm::vec2& moveSpeed, float angularSpeed, int updateOrder) :
        Component(updateOrder), m_MoveSpeed(moveSpeed), m_AngularSpeed(angularSpeed)
    {}

    void Simple2DMovementComponent::Update(float deltaTime)
    {
        Component::Update(deltaTime);

        glm::vec3 position = m_OwnerActor->GetTransform().GetPosition();
        position.x += m_MoveSpeed.x * deltaTime;
        position.y += m_MoveSpeed.y * deltaTime;
        m_OwnerActor->GetTransform().SetPosition(position);

        if (!Math::NearZero(m_AngularSpeed))
        {
            float rotation = m_OwnerActor->GetTransform().GetRotation().z;
            rotation += m_AngularSpeed * deltaTime;
            m_OwnerActor->GetTransform().SetRotation(glm::vec3(0.f,0.f,rotation));
        }
    }

    void Simple2DMovementComponent::SetMoveSpeed(const glm::vec2& speed)
    {
        m_MoveSpeed = speed;
    }

    void Simple2DMovementComponent::SetAngularSpeed(float speed)
    {
        m_AngularSpeed = speed;
    }
}
