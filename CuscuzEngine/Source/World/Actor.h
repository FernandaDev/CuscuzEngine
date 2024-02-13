#pragma once
#include "Utils/Log.h"
#include "World/Component.h"

class World;

class Actor
{
public:
    enum State
    {
        Active,
        Paused,
        Dead
    };
private:
    //ID?
    std::string m_name;
    State m_State;
    float m_X, m_Y; //TODO substitute for a vec2 later
    float m_Scale;
    float m_Rotation;
    std::vector<Component*> m_Components;
    World* m_World; // shared pointer?
    
public:
    Actor(World* World, std::string Name);
    Actor(const Actor& other):
    m_name(other.m_name), m_State(other.m_State),m_X(other.m_X),
    m_Y(other.m_Y), m_Scale(other.m_Scale), m_Rotation(other.m_Rotation),
    m_Components(other.m_Components), m_World(other.m_World)
    { }
    Actor& operator=(const Actor& other)
    {
        if(this != &other)
        {
            m_name = other.m_name;
            m_State = other.m_State;
            m_X = other.m_X;
            m_Y = other.m_Y;
            m_Scale = other.m_Scale;
            m_Rotation = other.m_Rotation;
            m_Components = other.m_Components;
            m_World = other.m_World;
        }
        
        return *this;
    }
    virtual ~Actor();

    void Update(float DeltaTime);

    template<typename T>
    T& AddComponent(T* Component);
    
    void RemoveComponent(Component* Component);

    State GetState() const { return m_State; }
    //World& GetWorld() const { return *m_World; } DO WE NEED THIS?

protected:
    void UpdateComponents(float DeltaTime) const;
    //virtual void UpdateActor(float DeltaTime);
};

template <typename T>
T& Actor::AddComponent(T* NewComponent)
{
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    
    m_Components.emplace_back(NewComponent);
    LOG_INFO("Added Component");
    NewComponent->SetOwner(this);
    return *NewComponent;
}
