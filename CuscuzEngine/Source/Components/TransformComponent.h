#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include "trigonometric.hpp"
#include "World/Component.h"


class TransformComponent : public Component
{
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
    
    glm::mat4 m_WorldTransform = glm::mat4(1);
    bool m_RecomputeWorldTransform = true;
    
public:
    TransformComponent() = delete;
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
    m_Position(position), m_Rotation(glm::quat(glm::radians(rotation))), m_Scale(scale) {}
    
    TransformComponent(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
    m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

    ~TransformComponent() override = default;

    void Update(float deltaTime) override;
    void OnAdded() override;
    void ImGuiDisplayComponent() override;
    
    glm::mat4 GetWorldTransform() const  { return m_WorldTransform; }

    std::string GetComponentType() const override { return "TransformComponent"; }
    
    void SetPosition(const glm::vec3& newPosition);
    void SetRotation(const glm::vec3& newRotation);
    void SetRotation(const glm::quat& newRotation);
    void SetScale(const glm::vec3& newScale);
    
    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::quat& GetRotation() const { return m_Rotation; }
    glm::vec3 GetEuler() const { return glm::eulerAngles(m_Rotation); }
    const glm::vec3& GetScale() const { return m_Scale; }
    glm::vec3 GetForward() const { return glm::normalize(glm::vec3(m_WorldTransform[2])); }

private:
    void ComputeWorldTransform();
};
