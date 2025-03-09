#pragma once

#include <memory>
#include <vector>
#include <string>

#include "vec3.hpp"

/*
    The SCENE will be the class that holds the spatial representation of objects.
    The WORLD will contain a vector of scenes, and any time a scene is loaded, the world will grab all is objects to the
    current Active Actors and start looping them of it's update.
*/
namespace Cuscuz
{
    class Actor;
    class Component;

    class World
    {
        std::vector<std::shared_ptr<Actor>> m_ActiveActors {};
        std::vector<std::shared_ptr<Actor>> m_PendingActors {};
        bool m_UpdatingActors = false;

    public:
        World() = default;
        ~World() = default;

        void Update(float deltaTime);
    
        Actor& CreateActor(std::string&& name, const glm::vec3& position = glm::vec3(0),
                           float scale = 1, float rotation = 0);
        void DestroyActor(Actor* actor) const;
        void ResetWorld();
        
        size_t GetActorsCount() const { return m_ActiveActors.size(); }
        std::vector<std::shared_ptr<Actor>> GetAllActors() const { return m_ActiveActors; }

    private:
        void HandleDeadActors();
    };
}