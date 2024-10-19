#pragma once

#include <memory>
#include <vector>
#include <string>

#include "vec2.hpp"

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
                    glm::vec2 position = glm::vec2(0,0),
                    float scale = 1, float rotation = 0);

    void DestroyActor(Actor* actor) const;

    void ResetWorld();

    size_t GetActorsCount() const { return m_ActiveActors.size(); }

    std::vector<std::shared_ptr<Actor>> GetAllActors() const
    { return m_ActiveActors; }

private:
    void HandleDeadActors();
};
