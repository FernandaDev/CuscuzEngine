#include "pch.h"

#include "Scene.h"
#include "Cuscuz/Render/IDrawable.h"
#include "Cuscuz/Core/OrthoCameraController.h"
#include "Cuscuz/Render/RenderCommand.h"
#include "Cuscuz/Render/Renderer2D.h"

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

    void Scene::OnRender(OrthoCameraController* camera) const
    {
        if (m_Drawables.empty())
            return;

        Renderer2D::ResetStats();

        RenderCommand::SetClearColor(m_ClearColor);
        RenderCommand::Clear();

        Renderer2D::BeginScene(camera->GetCamera());
        //Renderer::BeginScene(m_Camera->GetCamera()); for 3D objects

        for (const auto& drawable : m_Drawables)
        {
            drawable->Draw();
        }

        //Renderer::EndScene();
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
