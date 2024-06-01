#include "pch.h"
#include "Simple2DMovementComponent.h"

#include "Utils/Math.h"
#include "World/Actor.h"

Simple2DMovementComponent::Simple2DMovementComponent(float ForwardSpeed, float AngularSpeed, int UpdateOrder) :
    Component(UpdateOrder), m_ForwardSpeed(ForwardSpeed), m_AngularSpeed(AngularSpeed)
{
    m_Name = "Simple2DMovementComponent";
}

void Simple2DMovementComponent::Update(float DeltaTime)
{
    Component::Update(DeltaTime);

    if(!CC_Math::NearZero(m_ForwardSpeed))
    {
        glm::vec2 position = m_OwnerActor->GetPosition();
        position += m_OwnerActor->GetForward() * m_ForwardSpeed * DeltaTime;
        m_OwnerActor->SetPosition(position);
    }
    
    if(!CC_Math::NearZero(m_AngularSpeed))
    {
        float rotation = m_OwnerActor->GetRotation();
        rotation += m_AngularSpeed * DeltaTime;
        m_OwnerActor->SetRotation(rotation);
    }
}

void Simple2DMovementComponent::SetForwardSpeed(float Speed)
{
    m_ForwardSpeed = Speed;
}

void Simple2DMovementComponent::SetAngularSpeed(float Speed)
{
    m_AngularSpeed = Speed;
}
