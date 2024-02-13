#include "pch.h"
#include "Component.h"

void Component::SetOwner(Actor* OwnerActor)
{
    m_OwnerActor = OwnerActor;
}

void Component::Update(float DeltaTime)
{
}
