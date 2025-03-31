#include "pch.h"

#include "Level.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    Level::Level(std::string&& name) : m_Name(std::move(name))
    {}

    void Level::AddActor(const std::shared_ptr<Actor>& actor)
    {
        m_Actors.push_back(actor);
    }

    void Level::RemoveActor(const std::shared_ptr<Actor>& actor)
    {
        std::erase(m_Actors, actor);
    }
}