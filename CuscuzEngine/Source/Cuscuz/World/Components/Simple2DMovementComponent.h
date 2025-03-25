#pragma once

#include "vec2.hpp"
#include "Cuscuz/World/Component.h"

namespace Cuscuz
{
    class Simple2DMovementComponent : public Component
    {
        glm::vec2 m_MoveSpeed;
        float m_AngularSpeed;
    
    public:
        Simple2DMovementComponent() = default;
        Simple2DMovementComponent(const glm::vec2& moveSpeed, float angularSpeed, int updateOrder = 10);

        void Update(float deltaTime) override;

        const glm::vec2& GetMoveSpeed() const { return m_MoveSpeed; }
        float GetAngularSpeed() const { return m_AngularSpeed; }
        void SetMoveSpeed(const glm::vec2& speed);
        void SetAngularSpeed(float speed);

        DECLARE_CLASS_TYPE(Simple2DMovementComponent)
    protected:
        CLASS_TYPE_IMPLEMENT_WITH_BASE(Simple2DMovementComponent, Component)
    };
}