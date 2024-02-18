#include "pch.h"
#include "SDL_image.h"

#include "Utils/Log.h"
#include "Core/Window.h"
#include "RendererSystem.h"

#include "ResourceManager.h"
#include "World/Components/SpriteComponent.h"

RendererSystem::RendererSystem(Window* Window)
{
	m_Renderer = SDL_CreateRenderer(Window->GetWindow(), -1, 0);

	if (!m_Renderer)
		LOG_ERROR("Could not create a renderer.");

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		LOG_ERROR("Couldn't load SDL image!");
	}
}

RendererSystem::~RendererSystem()
{	
	if(m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
	
	IMG_Quit();

	m_SpriteComponents.clear();
}

void RendererSystem::AddSpriteComponent(std::shared_ptr<SpriteComponent> NewSpriteComponent)
{
	const int drawOrder = NewSpriteComponent->GetDrawOrder();
	auto it = m_SpriteComponents.begin();

	for( ; it != m_SpriteComponents.end(); ++it)
	{
		if(const auto sprite = it->lock())
			if(drawOrder < sprite->GetDrawOrder())
				break;
	}

	m_SpriteComponents.insert(it, NewSpriteComponent);
}

void RendererSystem::RemoveSpriteComponent(std::shared_ptr<SpriteComponent> SpriteComponent)
{
	//TODO
}

void RendererSystem::Update() const
{
	Clear();

	if (m_SpriteComponents.empty())
		return;
	
	for (const auto& spriteComponent : m_SpriteComponents)
	{
		if(const auto sprite = spriteComponent.lock())
			sprite->Draw(m_Renderer);
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