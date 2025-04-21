#pragma once

namespace Cuscuz
{
    class World;
    class Actor;

    class Level
    {
        std::string m_Name;
        std::vector<std::shared_ptr<Actor>> m_Actors;
        World* m_OwningWorld = nullptr;
        
    public:
        Level(std::string&& name);
        ~Level();
        
        void AddActor(const std::shared_ptr<Actor>& actor);
        void RemoveActor(const std::shared_ptr<Actor>& actor);

        void SetOwningWorld(World* world) { m_OwningWorld = world; }
        World* GetOwningWorld() const { return m_OwningWorld; }
        
        const std::vector<std::shared_ptr<Actor>>& GetAllActors() const { return m_Actors; }
        size_t GetActorsCount() const { return m_Actors.size(); }
        std::string_view GetName() const { return m_Name; }
    };
}
