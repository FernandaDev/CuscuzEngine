#pragma once

#include "Cuscuz/Render/Camera.h"
#include "Cuscuz/World/Component.h"

namespace Cuscuz
{
    class CameraComponent : public Component
    {
        Camera m_Camera;

    public:
        CameraComponent() :
        m_Camera(glm::mat4(1.f)){}
        CameraComponent(const glm::mat4& Projection) :
        m_Camera(Projection){}
        CameraComponent(const CameraComponent& other) = default;
        
        ~CameraComponent() override = default;

        DECLARE_CLASS_TYPE(SpriteRenderer)
    protected:
        CLASS_TYPE_IMPLEMENT_WITH_BASE(CameraComponent, Component)
    };
}
