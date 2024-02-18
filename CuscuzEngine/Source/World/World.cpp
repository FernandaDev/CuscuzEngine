#include "pch.h"
#include "World.h"

#include "Components/SpriteComponent.h"
#include "Core/EngineApplication.h"

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
    NewActor->OnComponentAddedDelegated().Add(this, &World::OnActorComponentAdded);
    
    (m_UpdatingActors ? m_PendingActors : m_ActiveActors).emplace_back(NewActor);
}

void World::RemoveActor(Actor* Actor)
{
    //TODO remove from the event
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


void World::OnActorComponentAdded(std::shared_ptr<Component> NewComponent)
{
    const auto spriteComponent = std::dynamic_pointer_cast<SpriteComponent>(NewComponent);
    if (!spriteComponent)
        return;

    // Is this the world's responsibility? The world handles all the actors, so I've decided to leave it here for now...
    EngineApplication::Get().CC_RendererSystem->AddSpriteComponent(spriteComponent);
}
