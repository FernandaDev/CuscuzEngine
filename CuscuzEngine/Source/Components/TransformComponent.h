#pragma once

#include "fwd.hpp"
#include "vec2.hpp"
#include "mat4x4.hpp"
#include "trigonometric.hpp"
#include "World/Component.h"

class TransformComponent : public Component
{
    glm::vec2 m_Position;
    glm::vec2 m_Scale;
    float m_Rotation;
    glm::mat4 m_WorldTransform;
    bool m_RecomputeWorldTransform;
    
public:
    TransformComponent() = delete;
    TransformComponent(glm::vec2 position, float scale, float rotation);
    ~TransformComponent() override = default;

    void Update(float deltaTime) override;
    void OnAdded() override;
    void ImGuiDisplayComponent() override;
    
    glm::mat4 GetWorldTransform() const  { return m_WorldTransform; }

    std::string GetComponentType() const override { return "TransformComponent"; }
    
    void SetPosition(const glm::vec2& newPosition);
    void SetRotation(float newRotation);
    void SetScale(glm::vec2 newScale);
    
    const glm::vec2& GetPosition() const { return m_Position; }
    float GetRotation() const { return m_Rotation; }
    glm::vec2 GetScale() const { return m_Scale; }
    glm::vec2 GetForward() const { return {glm::cos(m_Rotation), -glm::sin(m_Rotation)}; }

private:
    void ComputeWorldTransform();
};
