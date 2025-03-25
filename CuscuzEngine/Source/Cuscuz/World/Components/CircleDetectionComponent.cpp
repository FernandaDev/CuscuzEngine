#include "pch.h"

#include "CircleDetectionComponent.h"
#include "imgui.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    CircleDetectionComponent::CircleDetectionComponent(float radius):
    m_Radius(radius), m_IsOverlapping(false) {}

    void CircleDetectionComponent::SetRadius(float newRadius)
    {
        m_Radius = newRadius;
    }

    const glm::vec3& CircleDetectionComponent::GetCenter() const
    {
        return m_OwnerActor->GetTransform().GetPosition();
    }
    
    void CircleDetectionComponent::OnOverlapping(Actor* other)
    {
        LOG_INFO("{0} is overlapping with {1}", GetActor()->GetName(), other->GetName());
    }
    
    void CircleDetectionComponent::OnOverlapEnter(Actor* other)
    {
        LOG_INFO("{0} entered overlapping with {1}", GetActor()->GetName(), other->GetName());
    }
    
    void CircleDetectionComponent::OnOverlapExit(Actor* other)
    {
        LOG_INFO("{0} exited overlapping with {1}", GetActor()->GetName(), other->GetName());
    }
}