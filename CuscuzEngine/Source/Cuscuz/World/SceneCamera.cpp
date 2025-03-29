#include "pch.h"
#include "SceneCamera.h"

#include "gtc/matrix_transform.hpp"

namespace Cuscuz
{
    SceneCamera::SceneCamera()
    {
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::Orthographic;
        m_OrthographicSize = size;
        m_OrthographicNear = nearClip;
        m_OrthographicFar = farClip;

        RecalculateProjection();
    }

    void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::Perspective;
        m_PerspectiveFOV = fov;
        m_PerspectiveNear = nearClip;
        m_PerspectiveFar = farClip;
        
        RecalculateProjection();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographicSize(float size)
    {
        m_OrthographicSize = size;
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographicNearClip(float nearClip)
    {
        m_OrthographicNear = nearClip;
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographicFarClip(float farClip)
    {
        m_OrthographicFar = farClip;
        RecalculateProjection();
    }
    
    void SceneCamera::SetProjectionType(ProjectionType projectionType)
    {
        m_ProjectionType = projectionType;
        RecalculateProjection();
    }

    void SceneCamera::SetPerspectiveFOV(float size)
    {
        m_PerspectiveFOV = size;
        RecalculateProjection();
    }

    void SceneCamera::SetPerspectiveNearClip(float nearClip)
    {
        m_PerspectiveNear = nearClip;
        RecalculateProjection();
    }

    void SceneCamera::SetPerspectiveFarClip(float farClip)
    {
        m_PerspectiveFar = farClip;
        RecalculateProjection();
    }
    
    void SceneCamera::RecalculateProjection()
    {
        if(m_ProjectionType == ProjectionType::Orthographic)
        {
            const float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
            const float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
            const float orthoBottom = -m_OrthographicSize * 0.5f;
            const float orthoTop = m_OrthographicSize * 0.5f;

            m_Projection = glm::ortho(orthoLeft, orthoRight,
                                      orthoBottom, orthoTop,
                                      m_OrthographicNear, m_OrthographicFar);
        }
        else
        {
            m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
        }
        

    }
}
