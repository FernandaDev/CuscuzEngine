#include "pch.h"
#include "GL/glew.h"
#include "Utils/Log.h"
#include "Core/Window.h"
#include "RendererSystem.h"

#include "CC_Engine.h"
#include "Components/SpriteRenderer.h"

RendererSystem::~RendererSystem()
{
    m_RenderComponents.clear();
}

void RendererSystem::Init() const
{
    Clear();
}

void RendererSystem::AddRenderComponent(const std::shared_ptr<IRender>& renderComponent)
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

void RendererSystem::RemoveRenderComponent(const std::shared_ptr<IRender>& renderComponent)
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

void RendererSystem::Update()
{
    Clear();

    if (m_RenderComponents.empty())
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

void RendererSystem::Clear() const
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

