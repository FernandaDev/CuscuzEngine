#pragma once

#include "Components/CircleDetectionComponent.h"
#include "Utils/Math.h"

namespace Physics
{
    static bool CheckCollision(IOnOverlap& a, IOnOverlap& b)
    {
        const glm::vec2 diff = a.GetCenter() - b.GetCenter();
        const float distSq = CC_Math::LengthSq(diff.x, diff.y);

        float radiiSq = a.GetRadius() + b.GetRadius();
        radiiSq *= radiiSq;

        return distSq <= radiiSq;
    }
}
