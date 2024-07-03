#include "pch.h"
#include "Component.h"

void Component::SetOwner(Actor* ownerActor)
{
    m_OwnerActor = ownerActor;
}

void Component::Update(float deltaTime)
{
}
