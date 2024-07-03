#include "pch.h"
#include "CircleDetectionComponent.h"

#include "World/Actor.h"

CircleDetectionComponent::CircleDetectionComponent(float radius):
m_Radius(radius)
{
    m_Name = "Circle Detection";
}

void CircleDetectionComponent::SetRadius(float newRadius)
{
    m_Radius = newRadius;
}

const glm::vec2& CircleDetectionComponent::GetCenter() const
{
    return m_OwnerActor->GetPosition();
}
