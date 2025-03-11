#include "pch.h"

#include "Scene.h"
#include "Cuscuz/Render/IDrawable.h"
#include "Cuscuz/Render/Renderer2D.h"
#include "Cuscuz/Render/Camera.h"

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

    Scene::~Scene()
    {
        m_OnDrawableProxyAdded.Remove(this);
        m_OnDrawableProxyRemoved.Remove(this);
    }

    void Scene::OnRender(const OrthographicCamera& camera) const
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

    void Scene::OnProxyAdded(IDrawable* drawable)
    {
        m_Drawables.push_back(drawable);
    }

    void Scene::OnProxyRemoved(IDrawable* drawable)
    {
        auto it = std::remove(m_Drawables.begin(), m_Drawables.end(), drawable);
        m_Drawables.erase(it, m_Drawables.end());
    }
}
