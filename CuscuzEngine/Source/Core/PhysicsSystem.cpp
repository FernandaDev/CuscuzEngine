#include "pch.h"
#include "PhysicsSystem.h"

#include "Utils/Physics.h"
#include "World/Actor.h"
#include "Physics/IPhysics.h"
#include "Utils/Timer.h"

PhysicsSystem::~PhysicsSystem()
{
    m_DetectionComponents.clear();
}

void PhysicsSystem::AddDetectionComponent(const std::shared_ptr<IOnOverlap>& detectionComponent)
{
    m_DetectionComponents.emplace_back(detectionComponent);
}

void PhysicsSystem::RemoveDetectionComponent(const std::shared_ptr<IOnOverlap>& detectionComponent)
{
    auto it = std::remove_if(m_DetectionComponents.begin(), m_DetectionComponents.end(),
                           [detectionComponent](const auto& component)
                           {
                               if (const auto comp = component.lock())
                                   return comp.get() == detectionComponent.get();
                               return false;
                           });
    
    if(it != m_DetectionComponents.end())
        m_DetectionComponents.erase(it);
}

void PhysicsSystem::Update()
{
    if(m_DetectionComponents.size() <= 1)
        return;

    if(m_IntervalTimer.Elapsed() < m_PhysicsInterval)
        return;

    m_IntervalTimer.Reset();
    
    for (size_t i = 0; i < m_DetectionComponents.size(); ++i)
    {
        for (size_t j = i + 1; j < m_DetectionComponents.size(); ++j)
        {
            if(const auto& comp1 = m_DetectionComponents[i].lock();
               const auto& comp2 = m_DetectionComponents[j].lock())
            {
                if(Physics::CheckCollision(*comp1, *comp2))
                {
                    if(!comp1->IsOverlapping())
                    {
                        comp1->OnOverlapEnter(comp2->GetActor());
                        comp1->SetIsOverlapping(true);
                    }
                    else
                    {
                        comp1->OnOverlapping(comp2->GetActor());
                    }
                    
                    if(!comp2->IsOverlapping())
                    {
                        comp2->OnOverlapEnter(comp1->GetActor());
                        comp2->SetIsOverlapping(true);
                    }
                    else
                    {
                        comp2->OnOverlapping(comp1->GetActor());
                    }
                }
                else
                {
                    if(comp1->IsOverlapping())
                    {
                        comp1->OnOverlapExit(comp2->GetActor());
                        comp1->SetIsOverlapping(false);
                    }

                    if(comp2->IsOverlapping())
                    {
                        comp2->OnOverlapExit(comp1->GetActor());
                        comp2->SetIsOverlapping(false);
                    }
                }
            }
        }
    }
}
