#pragma once

#include "Cuscuz/Core/ObjectBase.h"

namespace Cuscuz
{
    class Actor;
    
    class Component : public ObjectBase
    {
    protected:
        Actor* m_OwnerActor;
        uint32_t m_UpdateOrder;
    
    public:
        Component(uint32_t updateOrder = 100) :
        m_OwnerActor(nullptr), m_UpdateOrder(updateOrder)
        {}

        ~Component() override = default;

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

        uint32_t GetUpdateOrder() const { return m_UpdateOrder; }

        void SetOwner(Actor* ownerActor);
        Actor* GetOwner() const { return m_OwnerActor; }

        virtual void Update(float deltaTime);
        virtual void OnAdded() {}
        virtual void OnRemoved() {}
        virtual void OnTransformUpdate() {}
        virtual void ImGuiDisplayComponent() {}

        DECLARE_CLASS_TYPE(Component)
    protected:
        CLASS_TYPE_IMPLEMENT(Component)
    };
}
