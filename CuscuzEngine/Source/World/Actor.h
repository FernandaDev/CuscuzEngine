#pragma once

#include "vec2.hpp"
#include "Utils/Log.h"
#include "Component.h"
#include "Events/EventDefinitions.h"
#include "Utils/Math.h"

class World;

DECLARE_EVENT(OnComponentAdded, const std::shared_ptr<Component>&)

class Actor
{
public:
    enum State
    {
        Active,
        Paused,
        Dead
    };
protected:
    //ID?
    std::string m_Name;
    State m_State;
    glm::vec2 m_Position;
    float m_Scale;
    float m_Rotation;
    std::vector<std::shared_ptr<Component>> m_Components;
    World* m_World;
    OnComponentAdded m_OnComponentAddedDelegate;

public:
    Actor(World* world, std::string name, glm::vec2 position,
        float scale = 1.f, float rotation = 0);
    Actor(const Actor& other):
    m_Name(other.m_Name), m_State(other.m_State), m_Position(other.m_Position)
    , m_Scale(other.m_Scale), m_Rotation(other.m_Rotation),
    m_Components(other.m_Components), m_World(other.m_World)
    { }
    Actor& operator=(const Actor& other)
    {
        if(this != &other)
        {
            m_Name = other.m_Name;
            m_State = other.m_State;
            m_Position = other.m_Position;
            m_Scale = other.m_Scale;
            m_Rotation = other.m_Rotation;
            m_Components = other.m_Components;
            m_World = other.m_World;
        }
        
        return *this;
    }
    virtual ~Actor();

    void Update(float deltaTime);
    void Destroy();

    template<typename T>
    T& AddComponent(T* component);
    void RemoveComponent(Component* component);

    const std::string& GetName() const { return m_Name; }
    State GetState() const { return m_State; }
    const glm::vec2& GetPosition() const { return m_Position; }
    float GetScale() const { return m_Scale; }
    float GetRotation() const { return m_Rotation; }
    glm::vec2 GetForward() const { return {CC_Math::Cos(m_Rotation), -CC_Math::Sin(m_Rotation)}; }

    void SetPosition(const glm::vec2& newPosition) { m_Position = newPosition; }
    void SetRotation(float newRotation) { m_Rotation = newRotation; }

    OnComponentAdded& GetOnComponentAddedDelegate() { return m_OnComponentAddedDelegate; }
    //World& GetWorld() const { return *m_World; } DO WE NEED THIS?

    const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_Components; }

protected:
    void UpdateComponents(float deltaTime) const;
    virtual void UpdateActor(float deltaTime){}
    void OnComponentAdded();

private:
    void TryRenderComponent(std::shared_ptr<Component> component);
    void TryRemoveRenderComponent();
};

template <typename T>
T& Actor::AddComponent(T* newComponent)
{
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    
    m_Components.emplace_back(newComponent);
    LOG_INFO("Added Component");
    newComponent->SetOwner(this);
    OnComponentAdded();
    return *newComponent;
}
