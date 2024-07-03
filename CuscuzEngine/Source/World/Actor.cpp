#include "pch.h"
#include "Actor.h"

#include "World.h"
#include "Core/CC_Application.h"
#include "Components/SpriteComponent.h"

Actor::Actor(World* world, std::string name, glm::vec2 position, float scale, float rotation) :
 m_Name(std::move(name)), m_State(Active), m_Position(position), m_Scale(scale), m_Rotation(rotation),
m_World(world)
{
    if(m_World)
        m_World->AddActor(this);
}

Actor::~Actor()
{
    LOG_INFO("Actor being removed!");
    
    m_Components.clear();
}

void Actor::Update(float deltaTime)
{    
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);
}

void Actor::RemoveComponent(Component* ComponentToRemove)
{
    const auto it = std::find_if(m_Components.begin(), m_Components.end(), 
        [ComponentToRemove](const std::shared_ptr<Component>& ptr)
        {
            return ptr.get() == ComponentToRemove;
        });
    
    if(it == m_Components.end())
    {
        LOG_WARN("Trying to remove an invalid component!");
        return;
    }

    ComponentToRemove->OnRemoved();
    LOG_INFO("Removed Component");
    m_Components.erase(it);
}

void Actor::Destroy()
{
    m_State = Dead;

    TryRemoveRenderComponent();
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
    
    CC_Application::Get().CC_RendererSystem->AddRenderComponent(renderComponent);
}

void Actor::TryRemoveRenderComponent()
{
    for (const auto& component : m_Components)
    {
        const auto renderComponent = std::dynamic_pointer_cast<IRender>(component);
        if (!renderComponent)
            continue;
    
        CC_Application::Get().CC_RendererSystem->RemoveRenderComponent(renderComponent);
    }
}
