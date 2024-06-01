#include "pch.h"
#include "CircleDetectionComponent.h"

#include "World/Actor.h"

CircleDetectionComponent::CircleDetectionComponent(float Radius):
m_Radius(Radius)
{
    m_Name = "Circle Detection";
}

void CircleDetectionComponent::SetRadius(float NewRadius)
{
    m_Radius = NewRadius;
}

const glm::vec2& CircleDetectionComponent::GetCenter() const
{
    return m_OwnerActor->GetPosition();
}
