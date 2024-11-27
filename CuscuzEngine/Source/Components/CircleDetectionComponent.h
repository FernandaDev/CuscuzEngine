#pragma once

#include "vec2.hpp"
#include "Physics/IPhysics.h"
#include "World/Component.h"

class CircleDetectionComponent : public Component, public IOnOverlap
{
    float m_Radius;
    bool m_IsOverlapping;

public:
    CircleDetectionComponent() = default;
    CircleDetectionComponent(float radius);
    ~CircleDetectionComponent() override = default;

    void SetRadius(float newRadius);
    float GetRadius() const override { return m_Radius; }

    const glm::vec2& GetCenter() const override;
    Actor* GetActor() const override { return GetOwner(); }
    
    void OnOverlapping(Actor* other) override;
    void OnOverlapEnter(Actor* other) override;
    void OnOverlapExit(Actor* other) override;
    bool IsOverlapping() const override { return m_IsOverlapping; }
    void SetIsOverlapping(bool isOverlapping) override { m_IsOverlapping = isOverlapping; }

    void ImGuiDisplayComponent() override;

    REGISTER_COMPONENT(CircleDetectionComponent);
};
