#include "pch.h"
#include "Actor.h"

#include "World.h"
#include "Core/CC_Engine.h"
#include "Components/SpriteRenderer.h"
#include "Core/PhysicsSystem.h"
#include "Core/RendererSystem.h"
#include "Physics/IPhysics.h"

Actor::~Actor()
{
    LOG_INFO("Actor being destroyed!");
    
    m_Components.clear();
}

void Actor::Destroy()
{
    m_State = Dead;

    TryRemoveRenderComponent();
    TryRemovePhysicsComponent();
}

void Actor::Update(float deltaTime)
{
    UpdateTransform(deltaTime);
    
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);

    UpdateTransform(deltaTime);
}

void Actor::UpdateTransform(float deltaTime) const
{
    m_Transform->Update(deltaTime);
    
    for (const auto& component : m_Components)
        component->OnTransformUpdate();
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

    if(const auto renderComponent = std::dynamic_pointer_cast<IRender>(latestComponent))
    {
        CC_Engine::Get().CC_RendererSystem->AddRenderComponent(renderComponent);
    }
    else if(const auto physicsComponent = std::dynamic_pointer_cast<IOnOverlap>(latestComponent))
    {
        CC_Engine::Get().CC_PhysicsSystem->AddDetectionComponent(physicsComponent);
    }
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

void Actor::TryRemovePhysicsComponent()
{
    for (const auto& component : m_Components)
    {
        const auto detectionComponent = std::dynamic_pointer_cast<IOnOverlap>(component);
        if (!detectionComponent)
            continue;
    
        CC_Engine::Get().CC_PhysicsSystem->RemoveDetectionComponent(detectionComponent);
    }
}