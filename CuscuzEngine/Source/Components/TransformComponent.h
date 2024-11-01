#pragma once

#include "fwd.hpp"
#include "vec2.hpp"
#include "mat4x4.hpp"
#include "trigonometric.hpp"
#include "World/Component.h"

class TransformComponent : public Component
{
    glm::vec2 m_Position;
    float m_Scale;
    float m_Rotation;
    glm::mat4 m_WorldTransform;
    bool m_RecomputeWorldTransform;
    
public:
    TransformComponent() = delete;
    TransformComponent(glm::vec2 position, float scale, float rotation);
    ~TransformComponent() override = default;

    void Update(float deltaTime) override;
    void OnAdded() override;
    
    glm::mat4 GetWorldTransform() const  { return m_WorldTransform; }

    std::string GetComponentType() const override { return "TransformComponent"; }
    
    void SetPosition(const glm::vec2& newPosition) { m_Position = newPosition; }
    const glm::vec2& GetPosition() const { return m_Position; }
    
    void SetRotation(float newRotation) { m_Rotation = newRotation; }
    float GetRotation() const { return m_Rotation; }

    void SetScale(float newScale) { m_Scale = newScale; } 
    float GetScale() const { return m_Scale; }
    
    glm::vec2 GetForward() const { return {glm::cos(m_Rotation), -glm::sin(m_Rotation)}; }

private:
    void ComputeWorldTransform();
};
