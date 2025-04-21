#include "pch.h"

#include "Scene.h"
#include "Cuscuz/Render/IDrawable.h"
#include "Cuscuz/Render/Renderer2D.h"
#include "Cuscuz/Render/EditorCamera.h"
#include "Cuscuz/World/SceneCamera.h"
#include "Cuscuz/World/Components/TransformComponent.h"

namespace Cuscuz
{
    DrawableProxyEvent Scene::m_OnDrawableProxyAdded;
    DrawableProxyEvent Scene::m_OnDrawableProxyRemoved;

    Scene::Scene()
    {
        m_Drawables.reserve(100);

        m_OnDrawableProxyAdded.Add(this, &Scene::OnProxyAdded);
        m_OnDrawableProxyRemoved.Add(this, &Scene::OnProxyRemoved);
    }

    Scene::Scene(SceneCamera* camera): m_MainCamera(camera),
    m_CameraTransform(new TransformComponent(glm::vec3(0.f),glm::vec3(0.f),glm::vec3(0.f)))
    {
        m_Drawables.reserve(100);

        m_OnDrawableProxyAdded.Add(this, &Scene::OnProxyAdded);
        m_OnDrawableProxyRemoved.Add(this, &Scene::OnProxyRemoved);
    }

    Scene::~Scene()
    {
        m_OnDrawableProxyAdded.Remove(this);
        m_OnDrawableProxyRemoved.Remove(this);
    }

    void Scene::SetMainCamera(SceneCamera* camera, TransformComponent* cameraTransform)
    {
        m_MainCamera = camera;
        m_CameraTransform = cameraTransform;
    }

    void Scene::OnRenderEditor(const EditorCamera& camera) const
    {
        if (m_Drawables.empty())
            return;

        Renderer2D::BeginScene(camera);

        for (const auto& drawable : m_Drawables)
        {
            drawable->Draw();
        }

        Renderer2D::EndScene();
    }

    void Scene::OnRender() const
    {
        if (m_Drawables.empty() || !m_MainCamera)
            return;

        Renderer2D::BeginScene(*m_MainCamera, m_CameraTransform->GetWorldTransform());

        for (const auto& drawable : m_Drawables)
        {
            drawable->Draw();
        }

        Renderer2D::EndScene();
    }

    void Scene::OnProxyAdded(IDrawable* drawable)
    {
        m_Drawables.push_back(drawable);
    }

    void Scene::OnProxyRemoved(IDrawable* drawable)
    {
        auto it = std::remove(m_Drawables.begin(), m_Drawables.end(), drawable);
        m_Drawables.erase(it, m_Drawables.end());
    }

    void Scene::OnViewPortResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        if(m_MainCamera)
            m_MainCamera->SetViewportSize(width, height);
    }
}
