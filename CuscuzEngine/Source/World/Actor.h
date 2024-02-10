#pragma once

class World;
class Component;

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
    virtual ~Actor();

    void Update(float DeltaTime);

    void AddComponent(Component* Component);
    void RemoveComponent(Component* Component);

    State GetState() const { return m_State; }
    //World& GetWorld() const { return *m_World; } DO WE NEED THIS?

protected:
    void UpdateComponents(float DeltaTime) const;
    //virtual void UpdateActor(float DeltaTime);
};
