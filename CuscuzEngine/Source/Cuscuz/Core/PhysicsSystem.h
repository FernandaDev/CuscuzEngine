#pragma once

#include <vector>
#include "Cuscuz/Utils/Timer.h"

namespace Cuscuz
{
    class IOnOverlap;
    class CircleDetectionComponent;
    
    class PhysicsSystem
    {
        std::vector<std::weak_ptr<IOnOverlap>> m_DetectionComponents;
        float m_PhysicsInterval = 0.2f;
        Timer m_IntervalTimer;

    public:
        PhysicsSystem() = default;
        ~PhysicsSystem();

        void AddDetectionComponent(const std::shared_ptr<IOnOverlap>& component);
        void RemoveDetectionComponent(const std::shared_ptr<IOnOverlap>& detectionComponent);

        void OnUpdate();
    };
}
