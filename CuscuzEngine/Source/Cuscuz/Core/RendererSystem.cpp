#include "pch.h"

#include "RendererSystem.h"

#include "Cuscuz/Render/IDrawable.h"
#include "Cuscuz/Utils/Log.h"
#include "Cuscuz/Render/RenderCommand.h"
#include "Cuscuz/Render/Renderer2D.h"

namespace Cuscuz
{
    RendererSystem::RendererSystem()
     : m_Camera(std::make_unique<OrthoCameraController>(static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), true))
    {}

    RendererSystem::~RendererSystem()
    {
        m_RenderComponents.clear();
    }

    void RendererSystem::AddRenderComponent(const std::shared_ptr<IDrawable>& renderComponent)
    {
        const int drawOrder = renderComponent->GetDrawOrder();
        auto it = m_RenderComponents.begin();

        for (; it != m_RenderComponents.end(); ++it)
        {
            if (const auto renderObject = it->lock())
                if (drawOrder < renderObject->GetDrawOrder())
                    break;
        }

        m_RenderComponents.insert(it, renderComponent);
    }

    void RendererSystem::RemoveRenderComponent(const std::shared_ptr<IDrawable>& renderComponent)
    {
        auto it = std::remove_if(m_RenderComponents.begin(), m_RenderComponents.end(),
                               [renderComponent](const auto& component)
                               {
                                   if (const auto comp = component.lock())
                                       return comp.get() == renderComponent.get();
                                   return false;
                               });
    
        if(it != m_RenderComponents.end())
            m_RenderComponents.erase(it);
    }

    void RendererSystem::OnUpdate(float deltaTime)
    {
        m_Camera->OnUpdate(deltaTime);

        Renderer2D::ResetStats();
    
        RenderCommand::SetClearColor(m_ClearColor);
        RenderCommand::Clear();
    
        if (m_RenderComponents.empty())
            return;

        Renderer2D::BeginScene(m_Camera->GetCamera());
        //Renderer::BeginScene(m_Camera->GetCamera()); for 3D objects

        DrawObjects();

        //Renderer::EndScene();
        Renderer2D::EndScene();
    }

    void RendererSystem::OnEvent(CuscuzEvent& event)
    {
        m_Camera->OnEvent(event);
    }

    void RendererSystem::DrawObjects()
    {
        auto it = m_RenderComponents.begin();
        while (it != m_RenderComponents.end())
        {
            if (const auto& renderObject = it->lock())
            {
                renderObject->Draw();
                ++it;
            }
            else
            {
                it = m_RenderComponents.erase(it);
            }
        }
    }
}