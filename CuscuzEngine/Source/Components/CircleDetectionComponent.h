#pragma once
#include "vec2.hpp"
#include "World/Component.h"

class CircleDetectionComponent : public Component
{
    float m_Radius;
    
public:
    CircleDetectionComponent(float Radius);
    ~CircleDetectionComponent() override = default;

    void SetRadius(float NewRadius);
    float GetRadius() const { return m_Radius; }

    const glm::vec2& GetCenter() const; 
};
