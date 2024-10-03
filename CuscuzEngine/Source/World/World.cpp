#include "pch.h"
#include "World.h"

#include "Actor.h"

void World::Update(float deltaTime)
{
    m_UpdatingActors = true;
    for (const auto& actor : m_ActiveActors)
    {
        actor->Update(deltaTime);
    }
    m_UpdatingActors = false;

    if(!m_PendingActors.empty())
    {
        for (auto& pendingActor : m_PendingActors)
            m_ActiveActors.emplace_back(pendingActor);
        
        m_PendingActors.clear();
    }
    
    HandleDeadActors();
}

void World::AddActor(Actor* NewActor)
{
    (m_UpdatingActors ? m_PendingActors : m_ActiveActors).emplace_back(NewActor);
}

void World::HandleDeadActors()
{
    auto iter = m_ActiveActors.begin();
    while (iter != m_ActiveActors.end())
    {
        if ((*iter)->GetState() == ActorState::Dead)
        {
            iter = m_ActiveActors.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void World::ResetWorld()
{
    for (const auto& actor : m_ActiveActors)
        actor->Destroy();

    for (auto& pendingActor : m_PendingActors)
        pendingActor.reset();

    m_PendingActors.clear();
    
    HandleDeadActors();
}
