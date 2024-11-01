#include "pch.h"
#include "Actor.h"

#include "World.h"
#include "Core/CC_Engine.h"
#include "Components/SpriteComponent.h"
#include "Core/RendererSystem.h"
#include "ext/matrix_transform.hpp"

Actor::Actor(World* world, std::string&& name, glm::vec2 position, float scale, float rotation) :
 m_Name(std::move(name)), m_State(Active), m_World(world), m_Position(position), m_Scale(scale),
m_Rotation(rotation), m_WorldTransform(glm::mat4(1.f)), m_RecomputeWorldTransform(true)
{ }

Actor::~Actor()
{
    LOG_INFO("Actor being destroyed!");
    
    m_Components.clear();
}

void Actor::Update(float deltaTime)
{
    ComputeWorldTransform();
    
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);

    ComputeWorldTransform();
}

void Actor::Destroy()
{
    m_State = Dead;

    TryRemoveRenderComponent();
}

void Actor::ComputeWorldTransform()
{
    if(!m_RecomputeWorldTransform)
        return;

    m_RecomputeWorldTransform = false;
    m_WorldTransform = glm::scale(m_WorldTransform, glm::vec3(m_Scale, m_Scale, m_Scale));
    m_WorldTransform = glm::rotate(m_WorldTransform, m_Rotation, glm::vec3(0,0,1.f));
    m_WorldTransform = glm::translate(m_WorldTransform, glm::vec3(m_Position.x, m_Position.y, 0.f));

    for (const auto& comp : m_Components)
        comp->OnTransformUpdate();
}

void Actor::UpdateComponents(float deltaTime) const
{
    if(m_Components.empty())
        return;
    
    for (const auto& component : m_Components)
        component->Update(deltaTime);
}

void Actor::OnComponentAdded()
{
    const auto latestComponent = m_Components.back();

    m_OnComponentAddedDelegate.Broadcast(latestComponent);
    
    TryRenderComponent(latestComponent);
}

void Actor::TryRenderComponent(std::shared_ptr<Component> component)
{
    const auto renderComponent = std::dynamic_pointer_cast<IRender>(component);
    if (!renderComponent)
        return;
    
    CC_Engine::Get().CC_RendererSystem->AddRenderComponent(renderComponent);
}

void Actor::TryRemoveRenderComponent()
{
    for (const auto& component : m_Components)
    {
        const auto renderComponent = std::dynamic_pointer_cast<IRender>(component);
        if (!renderComponent)
            continue;
    
        CC_Engine::Get().CC_RendererSystem->RemoveRenderComponent(renderComponent);
    }
}