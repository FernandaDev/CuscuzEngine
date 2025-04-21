#include "pch.h"

#include "World.h"
#include "Actor.h"
#include "Level.h"

namespace Cuscuz
{    
    World::World() : m_ActiveLevel(CreateAssetRef<Level>("default"))
    {}

    void World::LoadLevel(CC_AssetRef<Level>&& level) 
    {
        level->SetOwningWorld(this);

        if(m_ActiveLevel)
        {
            for (const auto& actor : m_ActiveActors)
                actor->Destroy();
        }
        
        m_ActiveLevel = std::move(level);
        m_PendingActors = m_ActiveLevel->GetAllActors();
    }

    void World::Update(float deltaTime)
    {
        m_UpdatingActors = true;
        for (auto& actor : m_ActiveActors)
        {
            actor->Update(deltaTime);
        }
        m_UpdatingActors = false;

        if(!m_PendingActors.empty())
        {
            for (auto& pendingActor : m_PendingActors)
            {
                m_ActiveActors.push_back(pendingActor);
            }
        
            m_PendingActors.clear();
        }
    
        HandleDeadActors();
    }

    Actor& World::CreateActor(std::string&& name, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
    {
        if(name.empty())
            name = "Actor";

        const std::shared_ptr<Actor>& actor = std::make_shared<Actor>(m_ActiveLevel, std::move(name), position, scale, rotation);
        m_ActiveLevel->AddActor(actor);
        m_PendingActors.push_back(actor);
        
        return *actor;
    }

    void World::DestroyActor(const std::shared_ptr<Actor>& actor) const
    {
        if(!m_ActiveLevel)
            return;
        
        m_ActiveLevel->RemoveActor(actor);
        actor->Destroy();
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
}