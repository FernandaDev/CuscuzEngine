#include "pch.h"
#include "Simple2DMovementComponent.h"

#include "Utils/Math.h"
#include "World/Actor.h"

Simple2DMovementComponent::Simple2DMovementComponent(float forwardSpeed, float angularSpeed, int updateOrder) :
    Component(updateOrder), m_ForwardSpeed(forwardSpeed), m_AngularSpeed(angularSpeed)
{}

void Simple2DMovementComponent::Update(float deltaTime)
{
    Component::Update(deltaTime);

    if(!CC_Math::NearZero(m_ForwardSpeed))
    {
        glm::vec2 position = m_OwnerActor->GetPosition();
        position += m_OwnerActor->GetForward() * m_ForwardSpeed * deltaTime;
        m_OwnerActor->SetPosition(position);
    }
    
    if(!CC_Math::NearZero(m_AngularSpeed))
    {
        float rotation = m_OwnerActor->GetRotation();
        rotation += m_AngularSpeed * deltaTime;
        m_OwnerActor->SetRotation(rotation);
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
