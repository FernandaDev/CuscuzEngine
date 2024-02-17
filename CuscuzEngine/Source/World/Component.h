#pragma once

class Actor;

class Component
{
protected:
    Actor* m_OwnerActor;
    int m_UpdateOrder;
    
public:
    Component(int UpdateOrder = 100) :
    m_OwnerActor(nullptr), m_UpdateOrder(UpdateOrder)
    {}
    Component(const Component& other): m_OwnerActor(other.m_OwnerActor),
    m_UpdateOrder(other.m_UpdateOrder){}
    Component& operator=(const Component& other)
    {
        if(this!=&other)
        {
            m_OwnerActor = other.m_OwnerActor;
            m_UpdateOrder = other.m_UpdateOrder;
        }
        return *this;
    }
    virtual ~Component() = default;

    void SetOwner(Actor* OwnerActor);
    virtual void Update(float DeltaTime);
    //virtual void OnAdded() {}
    //virtual void OnRemoved() {}
    int GetUpdateOrder() const { return m_UpdateOrder; }
};
