#pragma once

class Actor;

class Component
{
protected:
    Actor* m_OwnerActor;
    int m_UpdateOrder;
    
public:
    Component(Actor* OwnerActor, int UpdateOrder = 100);
    virtual ~Component();

    virtual void Update(float DeltaTime);
    int GetUpdateOrder() const { return m_UpdateOrder; }
};
