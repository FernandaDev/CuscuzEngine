#include "pch.h"
#include "Actor.h"

#include "Component.h"
#include "World.h"

Actor::Actor(World* World, std::string Name) : m_name(Name)
{
    // Add itself to world Active list
    m_World = World;
    World->AddActor(this);
}

Actor::~Actor()
{
    // Remove it self from the world's list
    LOG_INFO("Actor being removed!");
    m_World->RemoveActor(this);

    for (const Component* component : m_Components)
        delete component;

    m_Components.clear();
}

void Actor::Update(float DeltaTime)
{    
    UpdateComponents(DeltaTime);
    //UpdateActor(DeltaTime);
}

void Actor::RemoveComponent(Component* Component)
{
    const auto it = std::find(m_Components.begin(), m_Components.end(), Component);
    if(it == m_Components.end())
    {
        LOG_WARN("Trying to remove an invalid component!");
        return;
    }

    LOG_INFO("Removed Component");
    m_Components.erase(it);
}

void Actor::UpdateComponents(float DeltaTime) const
{
    if(m_Components.empty())
        return;
    
    for (const auto& component : m_Components)
        component->Update(DeltaTime);
}