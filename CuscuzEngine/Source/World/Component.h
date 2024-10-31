#pragma once

#include "Core/ClassRegistry.h"

class Actor;

class Component
{
protected:
    Actor* m_OwnerActor;
    int m_UpdateOrder;
    
public:
    Component(int updateOrder = 100) :
    m_OwnerActor(nullptr), m_UpdateOrder(updateOrder)
    {}

    virtual ~Component() = default;

    virtual std::string GetComponentType() const = 0;
    
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

    int GetUpdateOrder() const { return m_UpdateOrder; }

    void SetOwner(Actor* ownerActor);

    virtual void Update(float deltaTime);
    virtual void OnAdded() {}
    virtual void OnRemoved() {}
    virtual void OnTransformUpdate() {}
};
