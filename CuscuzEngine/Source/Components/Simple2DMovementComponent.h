#pragma once

#include "World/Component.h"

class Simple2DMovementComponent : public Component
{
    float m_ForwardSpeed;
    float m_AngularSpeed;
    
public:
    Simple2DMovementComponent(float ForwardSpeed, float AngularSpeed, int UpdateOrder = 10);

    void Update(float DeltaTime) override;

    float GetForwardSpeed() const { return m_ForwardSpeed; }
    float GetAngularSpeed() const { return m_AngularSpeed; }
    void SetForwardSpeed(float Speed);
    void SetAngularSpeed(float Speed);
};
