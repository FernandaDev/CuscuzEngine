#include "pch.h"
#include "Component.h"

namespace Cuscuz
{
    void Component::SetOwner(Actor* ownerActor)
    {
        m_OwnerActor = ownerActor;
    }

    void Component::Update(float deltaTime)
    {
    }
}