#pragma once

#include <memory>
#include <vector>
#include <string>

#include "vec3.hpp"

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
    
    Actor& CreateActor(std::string&& name,
                    const glm::vec3& position = glm::vec3(0),
                    const glm::vec3& rotation = glm::vec3(0), float scale = 1.f);

    void DestroyActor(Actor* actor) const;

    void ResetWorld();

    size_t GetActorsCount() const { return m_ActiveActors.size(); }

    std::vector<std::shared_ptr<Actor>> GetAllActors() const
    { return m_ActiveActors; }

private:
    void HandleDeadActors();
};
