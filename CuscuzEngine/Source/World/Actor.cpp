#include "pch.h"
#include "Actor.h"

#include "Component.h"
#include "World.h"
#include "Utils/Log.h"

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
}

void Actor::Update(float DeltaTime)
{
    LOG_INFO("Actor: {0}", m_name);
    
    UpdateComponents(DeltaTime);
    //UpdateActor(DeltaTime);
}

void Actor::UpdateComponents(float DeltaTime) const
{
    if(m_Components.empty())
        return;
    
    for (Component* component : m_Components)
        component->Update(DeltaTime);
}
