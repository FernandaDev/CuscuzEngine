#include "pch.h"
#include "TransformComponent.h"
#include "ext/matrix_transform.hpp"

TransformComponent::TransformComponent(glm::vec2 position, float scale, float rotation) :
m_Position(position), m_Scale(scale), m_Rotation(rotation),
m_WorldTransform(glm::mat4(1.f)), m_RecomputeWorldTransform(true)
{}

void TransformComponent::OnAdded()
{
    Component::OnAdded();
    
    ComputeWorldTransform();
}

void TransformComponent::Update(float deltaTime)
{
    Component::Update(deltaTime);

    ComputeWorldTransform();
}

void TransformComponent::ComputeWorldTransform()
{
    if(!m_RecomputeWorldTransform)
        return;

    m_RecomputeWorldTransform = false;
    m_WorldTransform = glm::scale(m_WorldTransform, glm::vec3(m_Scale, m_Scale, m_Scale));
    m_WorldTransform = glm::rotate(m_WorldTransform, m_Rotation, glm::vec3(0,0,1.f));
    m_WorldTransform = glm::translate(m_WorldTransform, glm::vec3(m_Position.x, m_Position.y, 0.f));
}
