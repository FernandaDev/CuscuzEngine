#pragma once

#include "World/Component.h"

class Simple2DMovementComponent : public Component
{
    float m_ForwardSpeed;
    float m_AngularSpeed;
    
public:
    Simple2DMovementComponent() = default;
    Simple2DMovementComponent(float forwardSpeed, float angularSpeed, int updateOrder = 10);

    void Update(float deltaTime) override;

    float GetForwardSpeed() const { return m_ForwardSpeed; }
    float GetAngularSpeed() const { return m_AngularSpeed; }
    void SetForwardSpeed(float speed);
    void SetAngularSpeed(float speed);

    REGISTER_COMPONENT(Simple2DMovementComponent);
};
