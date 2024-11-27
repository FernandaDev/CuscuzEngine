#include "pch.h"
#include "TransformComponent.h"

#include "imgui.h"
#include "ext/matrix_transform.hpp"
#include "Utils/Math.h"

TransformComponent::TransformComponent(glm::vec2 position, float scale, float rotation) :
m_Position(position), m_Scale(scale), m_Rotation(rotation),
m_WorldTransform(glm::mat4(1.f)), m_RecomputeWorldTransform(true)
{}

void TransformComponent::OnAdded()
{
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

void TransformComponent::ImGuiDisplayComponent()
{
    ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Transform");

    ImGui::Separator();

    ImGui::PushItemWidth(100.0f); 
        
    ImGui::Text("Position");

    auto pos = m_Position;
    
    ImGui::DragFloat("x##pos", &pos.x);
    ImGui::DragFloat("y##pos", &pos.y);

    SetPosition(pos);

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::Text("Rotation");
    
    auto rot = m_Rotation;

    ImGui::DragFloat("degrees", &rot);

    SetRotation(rot);
    
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
        
    ImGui::Text("Scale");

    auto scale = m_Scale;
    
    ImGui::DragFloat("x##scale", &scale.x);
    ImGui::DragFloat("y##scale", &scale.y);

    SetScale(scale);
    
    ImGui::PopItemWidth();
    
    ImGui::Dummy(ImVec2(0.0f, 3.0f));
    ImGui::Separator();
}