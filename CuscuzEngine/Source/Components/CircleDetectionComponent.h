#pragma once
#include "vec2.hpp"
#include "World/Component.h"

class [[nodiscard]] CircleDetectionComponent : public Component
{
    float m_Radius;
    
public:
    CircleDetectionComponent(float radius);
    ~CircleDetectionComponent() override = default;

    void SetRadius(float newRadius);
    float GetRadius() const { return m_Radius; }

    const glm::vec2& GetCenter() const;

    REGISTER_COMPONENT(CircleDetectionComponent);
};
