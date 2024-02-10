#include "pch.h"
#include "World.h"

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

void World::RemoveActor(Actor* Actor)
{
    //TODO
}

void World::HandleDeadActors()
{
    //TODO
    // std::vector<Actor*> deadActor; // fixed array?
    //
    // for (Actor* actor : m_ActiveActors)
    // {
    //     if(actor->GetState() == Actor::Dead)
    //     {
    //         deadActor.emplace_back(actor);
    //     }
    // }
    //
    // for (Actor* deadActor : deadActor)
    // {
    //     delete deadActor;
    // }
}
