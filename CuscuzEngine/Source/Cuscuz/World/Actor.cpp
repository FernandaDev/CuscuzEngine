#include "pch.h"
#include "Actor.h"

#include "World.h"
#include "Cuscuz/Components/SpriteRenderer.h"
#include "Cuscuz/Core/RendererSystem.h"

namespace Cuscuz
{
    Actor::Actor(World* world, std::string&& name, const glm::vec3& position, float scale, float rotation) :
    m_Name(std::move(name)), m_State(Active),
    m_Transform(std::make_unique<TransformComponent>(position, scale, rotation)),
    m_World(world)
    {}

    Actor::~Actor()
    {
        LOG_INFO("Actor being destroyed!");

        for (const auto& component : m_Components)
            component->OnRemoved();

        m_Components.clear();
    }

    void Actor::Destroy()
    {
        m_State = Dead;
    }

    void Actor::Update(float deltaTime)
    {
        UpdateTransform(deltaTime);

        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);

        UpdateTransform(deltaTime);
    }

    void Actor::UpdateTransform(float deltaTime) const
    {
        m_Transform->Update(deltaTime);

        for (const auto& component : m_Components)
            component->OnTransformUpdate();
    }

    void Actor::UpdateComponents(float deltaTime) const
    {
        if (m_Components.empty())
            return;

        for (const auto& component : m_Components)
            component->Update(deltaTime);
    }
}
