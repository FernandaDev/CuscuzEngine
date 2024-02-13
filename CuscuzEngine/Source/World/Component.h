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
    virtual ~Component() = default;

    void SetOwner(Actor* OwnerActor);
    virtual void Update(float DeltaTime);
    int GetUpdateOrder() const { return m_UpdateOrder; }
};
