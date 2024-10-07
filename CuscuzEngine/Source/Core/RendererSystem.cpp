#include "pch.h"
//#include "SDL_image.h"

#include "Utils/Log.h"
#include "Core/Window.h"
#include "RendererSystem.h"

#include "ResourceManager.h"
#include "Components/SpriteComponent.h"

RendererSystem::RendererSystem(Window* window)
{
    m_Renderer = SDL_CreateRenderer(window->GetWindow(), -1, 0);

    if (!m_Renderer)
        LOG_ERROR("Could not create a renderer.");

    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    // {
    //     LOG_ERROR("Couldn't load SDL image!");
    // }
}

RendererSystem::~RendererSystem()
{
    if (m_Renderer)
        SDL_DestroyRenderer(m_Renderer);

    //IMG_Quit();

    m_RenderComponents.clear();
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
            sprite->Draw(m_Renderer);
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
    SDL_RenderPresent(m_Renderer);
}

void RendererSystem::Clear() const
{
    SDL_RenderClear(m_Renderer);
}
