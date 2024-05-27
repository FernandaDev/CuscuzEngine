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
    std::weak_ptr<World> m_World;
    OnComponentAdded m_OnComponentAddedDelegate;

    friend class AppImGuiLayer;

public:
    Actor(std::shared_ptr<World> World, std::string Name, glm::vec2 Position,
        float Scale = 1.f, float Rotation = 0);
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

    void Update(float DeltaTime);
    void Destroy();

    template<typename T>
    T& AddComponent(T* Component);
    void RemoveComponent(Component* Component);

    const std::string& GetName() const { return m_Name; }
    State GetState() const { return m_State; }
    const glm::vec2& GetPosition() const { return m_Position; }
    float GetScale() const { return m_Scale; }
    float GetRotation() const { return m_Rotation; }
    const glm::vec2& GetForward() const { return glm::vec2(Math::Cos(m_Rotation), -Math::Sin(m_Rotation)); }

    void SetPosition(const glm::vec2& NewPosition) { m_Position = NewPosition; }
    void SetRotation(float NewRotation) { m_Rotation = NewRotation; }

    OnComponentAdded& GetOnComponentAddedDelegate() { return m_OnComponentAddedDelegate; }
    //World& GetWorld() const { return *m_World; } DO WE NEED THIS?

protected:
    void UpdateComponents(float DeltaTime) const;
    virtual void UpdateActor(float DeltaTime){}
    void OnComponentAdded();

private:
    void TryRenderComponent(std::shared_ptr<Component> Component);
    void TryRemoveRenderComponent();
};

template <typename T>
T& Actor::AddComponent(T* NewComponent)
{
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    
    m_Components.emplace_back(NewComponent);
    LOG_INFO("Added Component");
    NewComponent->SetOwner(this);
    OnComponentAdded();
    return *NewComponent;
}
