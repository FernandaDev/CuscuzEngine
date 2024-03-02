#include "pch.h"
#include "Actor.h"

#include "World.h"

Actor::Actor(std::shared_ptr<World> World, std::string Name, glm::vec2 Position, float Scale, float Rotation) :
 m_Name(std::move(Name)), m_State(Active), m_Position(Position), m_Scale(Scale), m_Rotation(Rotation),
m_World(World)
{
    if(const auto world = m_World.lock())
        world->AddActor(this);
}

Actor::~Actor()
{
    LOG_INFO("Actor being removed!");

    if(const auto world = m_World.lock())
        world->RemoveActor(this);
    
    m_Components.clear();
}

void Actor::Update(float DeltaTime)
{    
    UpdateComponents(DeltaTime);
    UpdateActor(DeltaTime);
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
    
    LOG_INFO("Removed Component");
    m_Components.erase(it);
}

void Actor::Destroy()
{
    m_State = Dead;
}

void Actor::UpdateComponents(float DeltaTime) const
{
    if(m_Components.empty())
        return;
    
    for (const auto& component : m_Components)
        component->Update(DeltaTime);
}
