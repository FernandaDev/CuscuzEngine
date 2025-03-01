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
        glm::vec2 m_Scale;
        float m_Rotation;
        glm::mat4 m_WorldTransform;
        bool m_RecomputeWorldTransform;
    
    public:
        TransformComponent() = delete;
        TransformComponent(const glm::vec3& position, float scale, float rotation);
        ~TransformComponent() override = default;

        void Update(float deltaTime) override;
        void OnAdded() override;
        void ImGuiDisplayComponent() override;
    
        glm::mat4 GetWorldTransform() const  { return m_WorldTransform; }

        std::string GetComponentType() const override { return "TransformComponent"; }
    
        void SetPosition(const glm::vec3& newPosition);
        void SetRotation(float newRotation);
        void SetScale(glm::vec2 newScale);
    
        const glm::vec3& GetPosition() const { return m_Position; }
        float GetRotation() const { return m_Rotation; }
        glm::vec2 GetScale() const { return m_Scale; }
        glm::vec3 GetForward() const { return {glm::cos(m_Rotation), -glm::sin(m_Rotation), 1.0f}; }

    private:
        void ComputeWorldTransform();
    };
}