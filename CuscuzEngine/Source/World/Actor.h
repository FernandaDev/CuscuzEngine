#pragma once

#include "vec2.hpp"
#include "Utils/Log.h"
#include "Component.h"
#include "Components/TransformComponent.h"
#include "Events/EventDefinitions.h"

class World;

DECLARE_EVENT(OnComponentAdded, const std::shared_ptr<Component>&)

enum ActorState
{
    Active,
    Paused,
    Dead
};

class Actor
{
    
protected:
    std::string m_Name;
    ActorState m_State;
    std::vector<std::shared_ptr<Component>> m_Components {};
    World* m_World;
    OnComponentAdded m_OnComponentAddedDelegate {};

    std::unique_ptr<TransformComponent> m_Transform;

public:
    Actor(World* world, std::string&& name, glm::vec2 position,
        float scale = 1.f, float rotation = 0);
    virtual ~Actor();

    void Update(float deltaTime);
    void Destroy();

    const std::string& GetName() const { return m_Name; }
    ActorState GetState() const { return m_State; }
    TransformComponent& GetTransform() const { return *m_Transform; }
    const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_Components; }

protected:
    void UpdateComponents(float deltaTime) const;
    virtual void UpdateActor(float deltaTime){}
    void OnComponentAdded();

private:
    void TryRenderComponent(std::shared_ptr<Component> component);
    void TryRemoveRenderComponent();
    void UpdateTransform(float deltaTime) const;
    
    ///////////////TEMPLATES//////////////////
public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        auto& newComponent = m_Components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
        newComponent->SetOwner(this);
        OnComponentAdded();
        LOG_INFO("{0} was added to {1}.", T::GetStaticComponentType(), m_Name);
        return *std::static_pointer_cast<T>(newComponent);
    }

    void AddComponent(Component* component)
    {
        const auto& newComponent = m_Components.emplace_back(component);
        newComponent->SetOwner(this);
        LOG_INFO("{0} was added to {1}.", newComponent->GetComponentType(), m_Name);
        OnComponentAdded();
    }

    template<typename T>
    T& GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        for (const auto& component : m_Components)
        {
            if(auto comp = std::dynamic_pointer_cast<T>(component))
            {
                LOG_INFO("Got {0} from {1}.", T::GetStaticComponentType(), m_Name);
                return *comp;
            }
        }

        throw std::runtime_error("Component not found!");
    }

    template<typename T>
    bool HasComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        for (const auto& component : m_Components)
        {
            if(std::dynamic_pointer_cast<T>(component)) // quem tem Animation2D has um sprite component, entao ele entra.
            {
                LOG_INFO("{0} has {1}.", m_Name, T::GetStaticComponentType() );
                return true;
            }
        }

        return false;
    }
    
    // Note: this function will remove the specific component and will not try to cast to another component.
    template<typename T>
    bool RemoveComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        
        const auto it = std::find_if(m_Components.begin(), m_Components.end(), 
        [](const std::shared_ptr<Component>& component)
        {
            return component->GetComponentType() == T::GetStaticComponentType();
        });
    
        if(it == m_Components.end())
        {
            LOG_WARN("Trying to remove an invalid component!");
            return false;
        }
        
        it->OnRemoved();
        LOG_INFO("{0} was removed from {1}.", T::GetStaticComponentType(), m_Name );
        m_Components.erase(it);
        return true;
    }
};