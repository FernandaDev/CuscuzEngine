#pragma once

class Actor;

class Component
{
protected:
    Actor* m_OwnerActor;
    int m_UpdateOrder;
    std::string m_Name; // for debug
    
public:
    Component(int UpdateOrder = 100) :
    m_OwnerActor(nullptr), m_UpdateOrder(UpdateOrder), m_Name("Component")
    {}
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
    virtual ~Component() = default;

    std::string_view GetName() const { return m_Name; }
    void SetOwner(Actor* OwnerActor);
    virtual void Update(float DeltaTime);
    //virtual void OnAdded() {}
    //virtual void OnRemoved() {}
    int GetUpdateOrder() const { return m_UpdateOrder; }
};
