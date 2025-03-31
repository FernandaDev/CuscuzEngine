#pragma once

#include <string>
#include "vec3.hpp"
#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    class Level;
    class Actor;

    class World
    {
        std::vector<std::shared_ptr<Actor>> m_ActiveActors {};
        std::vector<std::shared_ptr<Actor>> m_PendingActors {};
        bool m_UpdatingActors = false;

        std::unordered_map<std::string, CC_AssetRef<Level>> m_Levels;
        CC_AssetRef<Level> m_ActiveLevel;
        
    public:
        World() = default;
        ~World() = default;

        void Update(float deltaTime);
        
        void AddLevel(const CC_AssetRef<Level>& level);
        void SetActiveLevel(const std::string& levelName);
        const CC_AssetRef<Level>& GetActiveLevel() { return m_ActiveLevel; }

        Actor& CreateActor(std::string&& name, const glm::vec3& position = glm::vec3(0),
                           float scale = 1, float rotation = 0);
        void DestroyActor(const std::shared_ptr<Actor>& actor) const;

    private:
        void HandleDeadActors();
    };
}
