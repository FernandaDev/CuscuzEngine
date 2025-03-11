#include "pch.h"
#include "Camera.h"

#include "imgui.h"
#include "gtc/matrix_transform.hpp"
#include "Cuscuz/Utils/Math.h"

namespace Cuscuz
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ViewMatrix(1.0f), m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
        m_Position(0.f), m_Rotation(0.f)
    {
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        if(position == m_Position)
            return;

        m_Position = position;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation)
    {
        if(FLOAT_EQUAL(rotation, m_Rotation))
            return;

        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_Position);
        transformMatrix = glm::rotate(transformMatrix, glm::radians(m_Rotation), glm::vec3(0,0,1.f));

        m_ViewMatrix = glm::inverse(transformMatrix);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}