#include "pch.h"
#include "SDL_image.h"

#include "Utils/Log.h"
#include "Window.h"
#include "RendererSystem.h"

#include "ResourceManager.h"

#define MAX_SPRITE_AMOUNT 24

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
	
	m_Sprites.reserve(MAX_SPRITE_AMOUNT);
}

RendererSystem::~RendererSystem()
{
	if(m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
	
	m_Sprites.clear();
	
	IMG_Quit();
}

std::shared_ptr<Sprite> RendererSystem::CreateSprite(const std::string& FilePath)
{
	return CreateSprite(FilePath, 0, 0);
}

std::shared_ptr<Sprite> RendererSystem::CreateSprite(const std::string& FilePath, int X, int Y)
{
	return CreateSprite(FilePath, X, Y, 1, 1);
}

std::shared_ptr<Sprite> RendererSystem::CreateSprite(const std::string& FilePath, int X, int Y, float SizeX, float SizeY)
{
	if (m_Sprites.size() >= MAX_SPRITE_AMOUNT)
	{
		LOG_WARN("Cannot load more textures!");
		return nullptr;
	}

	std::weak_ptr<Texture> newTexture = ResourceManager::Instance().GetTexture(m_Renderer, FilePath);

	auto newSprite = std::make_shared<Sprite>(newTexture, X, Y, SizeX, SizeY);
	m_Sprites.emplace_back(newSprite);

	return newSprite;
}

// Note: somewhere else, the sprites X and Y are going to be set.
void RendererSystem::Update() const
{
	Clear();

	if (m_Sprites.empty())
		return;

	for (const std::shared_ptr<Sprite>& sprite : m_Sprites)
	{
		Blit(*sprite);
	}
}

void RendererSystem::Render() const
{
	SDL_RenderPresent(m_Renderer);
}

//PRIVATE

void RendererSystem::Blit(const Sprite& Sprite) const
{
	const SDL_Rect dest{Sprite.GetX(), Sprite.GetY(),
						Sprite.GetWidth(), Sprite.GetHeight()};

	const Texture* texture = Sprite.GetTexture();

	if(!texture)
		return;
	
	SDL_RenderCopy(m_Renderer, texture->GetSDLPtr(), NULL, &dest);
}

void RendererSystem::Clear() const
{
	SDL_RenderClear(m_Renderer);
}