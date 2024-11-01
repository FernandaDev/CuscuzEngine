#include "pch.h"
#include "Actor.h"

#include "World.h"
#include "Core/CC_Engine.h"
#include "Components/SpriteComponent.h"
#include "Core/RendererSystem.h"

Actor::Actor(World* world, std::string&& name, glm::vec2 position, float scale, float rotation) :
 m_Name(std::move(name)), m_State(Active), m_World(world),
m_Transform(std::make_unique<TransformComponent>(position, scale, rotation))
{ }

Actor::~Actor()
{
    LOG_INFO("Actor being destroyed!");
    
    m_Components.clear();
}

void Actor::Destroy()
{
    m_State = Dead;

    TryRemoveRenderComponent();
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


