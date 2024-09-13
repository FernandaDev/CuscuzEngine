#pragma once

class Actor;

class Component
{
protected:
    Actor* m_OwnerActor;
    int m_UpdateOrder;
    std::string m_Name; // for debug
    
public:
    Component(int updateOrder = 100) :
    m_OwnerActor(nullptr), m_UpdateOrder(updateOrder), m_Name("Component")
    {}

    virtual ~Component() = default;

    Component(const Component& other): m_OwnerActor(other.m_OwnerActor),
    m_UpdateOrder(other.m_UpdateOrder), m_Name(other.m_Name){}

    Component& operator=(const Component& other)
    {
        if(this!=&other)
        {
            m_OwnerActor = other.m_OwnerActor;
            m_UpdateOrder = other.m_UpdateOrder;
            m_Name = other.m_Name;
        }
        return *this;
    }

    std::string_view GetName() const { return m_Name; }
    int GetUpdateOrder() const { return m_UpdateOrder; }

    void SetOwner(Actor* ownerActor);

    virtual void Update(float deltaTime);
    virtual void OnAdded() {}
    virtual void OnRemoved() {}
};
