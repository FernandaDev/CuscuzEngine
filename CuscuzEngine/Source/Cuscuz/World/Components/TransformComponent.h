#pragma once

#include "fwd.hpp"
#include "vec2.hpp"
#include "mat4x4.hpp"
#include "trigonometric.hpp"
#include "Cuscuz/World/Component.h"

namespace Cuscuz
{
    class TransformComponent : public Component
    {
        glm::vec3 m_Position;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
        
        glm::mat4 m_WorldTransform;
        bool m_RecomputeWorldTransform;
    
    public:
        TransformComponent() = delete;
        TransformComponent(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);
        ~TransformComponent() override = default;

        void Update(float deltaTime) override;
        void OnAdded() override;
    
        glm::mat4 GetWorldTransform() const  { return m_WorldTransform; }

        void SetPosition(const glm::vec3& newPosition);
        void SetRotation(const glm::vec3& newRotation);
        void SetScale(const glm::vec3& newScale);
    
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetRotation() const { return m_Rotation; }
        const glm::vec3& GetScale() const { return m_Scale; }

        //glm::vec3 GetForward() const { return {glm::cos(m_Rotation), -glm::sin(m_Rotation), 1.0f}; }

        DECLARE_CLASS_TYPE(TransformComponent)
    protected:
        CLASS_TYPE_IMPLEMENT_WITH_BASE(TransformComponent, Component)
    private:
        void ComputeWorldTransform();
    };
}