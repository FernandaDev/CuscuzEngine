#pragma once

#include "Cuscuz/Render/Camera.h"
#include "Cuscuz/World/Component.h"
#include "Cuscuz/World/SceneCamera.h"

namespace Cuscuz
{
    class CameraComponent : public Component
    {
        SceneCamera m_Camera;

    public:
        CameraComponent() = default;
        CameraComponent(const glm::mat4& projection) :
        m_Camera(projection) {}
        CameraComponent(const CameraComponent& other) = default;
        ~CameraComponent() override = default;

        SceneCamera& GetCamera() { return m_Camera; }        

        DECLARE_CLASS_TYPE(CameraComponent)
    protected:
        CLASS_TYPE_IMPLEMENT_WITH_BASE(CameraComponent, Component)
    };
}
