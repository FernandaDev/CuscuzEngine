#include "pch.h"

#include "TransformComponent.h"
#include "gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"

namespace Cuscuz
{
    TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation) :
    m_Position(position), m_Scale(scale), m_Rotation(rotation),
    m_WorldTransform(glm::mat4(1.f)), m_RecomputeWorldTransform(true)
    {}

    void TransformComponent::OnAdded()
    {
        ComputeWorldTransform();
    }

    void TransformComponent::SetPosition(const glm::vec3& newPosition)
    {
        if(newPosition == m_Position)
            return;

        m_Position = newPosition;
        m_RecomputeWorldTransform = true;
    }

    void TransformComponent::SetRotation(const glm::vec3& newRotation)
    {
        if(m_Rotation == newRotation)
            return;

        m_Rotation = newRotation;
        m_RecomputeWorldTransform = true;
    }

    void TransformComponent::SetScale(const glm::vec3& newScale)
    {
        if(newScale == m_Scale)
            return;

        m_Scale = newScale;
        m_RecomputeWorldTransform = true;
    }

    void TransformComponent::Update(float deltaTime)
    {
        ComputeWorldTransform();
    }

    void TransformComponent::ComputeWorldTransform()
    {
        if(!m_RecomputeWorldTransform)
            return;

        m_RecomputeWorldTransform = false;

        m_WorldTransform = glm::translate(glm::mat4(1.0f), m_Position)
                         * glm::toMat4(glm::quat(m_Rotation))
                         * glm::scale(glm::mat4(1.0f), m_Scale);
        
        // m_WorldTransform = glm::mat4(1.0f); 
        //
        // m_WorldTransform = glm::translate(m_WorldTransform, glm::vec3(m_Position.x, m_Position.y, m_Position.z));
        // m_WorldTransform = glm::rotate(m_WorldTransform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        // m_WorldTransform = glm::scale(m_WorldTransform, glm::vec3(m_Scale.x, m_Scale.y, 1.0f));
    }
}
