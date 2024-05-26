#include "pch.h"
#include "World.h"

#include "Actor.h"

void World::Update(float DeltaTime)
{
    m_UpdatingActors = true;
    for (const auto& actor : m_ActiveActors)
    {
        actor->Update(DeltaTime);
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

void World::RemoveActor(Actor* ActorToRemove)
{
}

void World::HandleDeadActors()
{
    auto iter = m_ActiveActors.begin();
    while (iter != m_ActiveActors.end())
    {
        if ((*iter)->GetState() == Actor::Dead)
        {
            iter = m_ActiveActors.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}
