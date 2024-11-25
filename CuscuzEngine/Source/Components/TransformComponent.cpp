#include "pch.h"
#include "TransformComponent.h"
#include "ext/matrix_transform.hpp"
#include "Utils/Math.h"

TransformComponent::TransformComponent(glm::vec2 position, float scale, float rotation) :
m_Position(position), m_Scale(scale), m_Rotation(rotation),
m_WorldTransform(glm::mat4(1.f)), m_RecomputeWorldTransform(true)
{}

void TransformComponent::OnAdded()
{
    Component::OnAdded();
    
    ComputeWorldTransform();
}

void TransformComponent::SetPosition(const glm::vec2& newPosition)
{
    if(newPosition == m_Position)
        return;

    m_Position = newPosition;
    m_RecomputeWorldTransform = true;
}

void TransformComponent::SetRotation(float newRotation)
{
    if(FLOAT_EQUAL(newRotation, m_Rotation))
        return;

    m_Rotation = newRotation;
    m_RecomputeWorldTransform = true;
}

void TransformComponent::SetScale(glm::vec2 newScale)
{
    if(newScale == m_Scale)
        return;

    m_Scale = newScale;
    m_RecomputeWorldTransform = true;
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
    
    m_WorldTransform = glm::mat4(1.0f); 
    
    m_WorldTransform = glm::translate(m_WorldTransform, glm::vec3(m_Position.x, m_Position.y, 0.f));
    m_WorldTransform = glm::rotate(m_WorldTransform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_WorldTransform = glm::scale(m_WorldTransform, glm::vec3(m_Scale.x, m_Scale.y, 1.0f));
}
