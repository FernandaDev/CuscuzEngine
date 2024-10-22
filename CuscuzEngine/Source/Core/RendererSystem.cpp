#include "pch.h"
#include "GL/glew.h"
#include "Utils/Log.h"
#include "Core/Window.h"
#include "RendererSystem.h"

#include "CC_Engine.h"
#include "Components/SpriteComponent.h"

RendererSystem::~RendererSystem()
{
    m_RenderComponents.clear();
}

void RendererSystem::Init() const
{
    Clear();
}

void RendererSystem::AddRenderComponent(std::shared_ptr<IRender> NewRenderComponent)
{
    const int drawOrder = NewRenderComponent->GetDrawOrder();
    auto it = m_RenderComponents.begin();

    for (; it != m_RenderComponents.end(); ++it)
    {
        if (const auto sprite = it->lock())
            if (drawOrder < sprite->GetDrawOrder())
                break;
    }

    m_RenderComponents.insert(it, NewRenderComponent);
}

void RendererSystem::RemoveRenderComponent(std::shared_ptr<IRender> renderComponent)
{
    auto it = std::remove_if(m_RenderComponents.begin(), m_RenderComponents.end(),
                           [renderComponent](const auto& spriteComponent)
                           {
                               if (const auto sprite = spriteComponent.lock())
                                   return sprite.get() == renderComponent.get();
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
    
     auto it = m_RenderComponents.begin();
     while (it != m_RenderComponents.end())
     {
         if (const auto& sprite = it->lock())
         {
             sprite->Draw();
             ++it;
         }
         else
         {
             it = m_RenderComponents.erase(it);
         }
     }
}

void RendererSystem::Render() const
{
    SDL_GL_SwapWindow(CC_Engine::Get().CC_Window->GetWindow());
}

void RendererSystem::Clear() const
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
