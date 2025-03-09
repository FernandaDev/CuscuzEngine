#pragma once

#include "Cuscuz/Components/CircleDetectionComponent.h"
#include "Cuscuz/Utils/Math.h"

namespace Cuscuz
{
    namespace Physics
    {
        static bool CheckCollision(IOnOverlap& a, IOnOverlap& b)
        {
            const glm::vec2 diff = a.GetCenter() - b.GetCenter();
            const float distSq = Math::LengthSq(diff.x, diff.y);

            float radiiSq = a.GetRadius() + b.GetRadius();
            radiiSq *= radiiSq;

            return distSq <= radiiSq;
        }
    }
}
