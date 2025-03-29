#pragma once

#include "Cuscuz/Render/Camera.h"

namespace Cuscuz
{
    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType { Orthographic = 0, Perspective = 1 };
    
    private:
        ProjectionType m_ProjectionType = ProjectionType::Orthographic;

        float m_OrthographicSize = 10.f;
        float m_OrthographicNear = -1.0f;
        float m_OrthographicFar = 1.0f;

        float m_PerspectiveFOV = glm::radians(45.f);
        float m_PerspectiveNear = 0.01f;
        float m_PerspectiveFar = 1000.f;

        float m_AspectRatio = 0.0f;

    public:
        SceneCamera();
        SceneCamera(const glm::mat4& projection) : Camera(projection) {}
        ~SceneCamera() override = default;

        ProjectionType GetProjectionType() const { return m_ProjectionType; }
        void SetProjectionType(ProjectionType projectionType);
        
        void SetOrthographic(float size, float nearClip, float farClip);
        void SetPerspective(float fov, float nearClip, float farClip);
        
        void SetViewportSize(uint32_t width, uint32_t height);

        void SetOrthographicSize(float size);
        float GetOrthographicSize() const { return m_OrthographicSize; }
        void SetOrthographicNearClip(float nearClip);
        float GetOrthographicNearClip() const { return m_OrthographicNear; }
        void SetOrthographicFarClip(float farClip);
        float GetOrthographicFarClip() const { return m_OrthographicFar; }

        void SetPerspectiveFOV(float size);
        float GetPerspectiveFOV() const { return m_PerspectiveFOV; }
        void SetPerspectiveNearClip(float nearClip);
        float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
        void SetPerspectiveFarClip(float farClip);
        float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
    private:
        void RecalculateProjection();
    };
}
