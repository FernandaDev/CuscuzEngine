
#include <SDL_image.h>
#include "Utils/Log.h"
#include "Window.h"

#include "RendererSystem.h"

#define IMAGE_ROOT_PATH "Source/Assets/Images/"
#define MAX_SPRITE_AMOUNT 24

RendererSystem::RendererSystem(Window* Window):
	m_Renderer{nullptr}
{
	m_Renderer = SDL_CreateRenderer(Window->GetWindow(), -1, 0);

	if (!m_Renderer)
		LOG_ERROR("Could not create a renderer.");

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	
	m_Sprites.reserve(MAX_SPRITE_AMOUNT);

	LOG_INFO("RendererSystem initialized.");
}

RendererSystem::~RendererSystem()
{
	if(m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
}

void RendererSystem::CreateSprite(const std::string& FilePath)
{
	CreateSprite(FilePath, 0, 0);
}

void RendererSystem::CreateSprite(const std::string& FilePath, int X, int Y)
{
	CreateSprite(FilePath, X, Y, 1, 1);
}

void RendererSystem::CreateSprite(const std::string& FilePath, int X, int Y, int SizeX, int SizeY)
{
	if (m_Sprites.size() >= MAX_SPRITE_AMOUNT)
	{
		LOG_WARN("Cannot load more textures!");
		return;
	}

	SDL_Texture* newTexture = LoadTexture(FilePath);

	if (!newTexture)
	{
		LOG_ERROR("Couldn't load the texture!");
		return;
	}

	m_Sprites.emplace_back(new Sprite{newTexture, X, Y, SizeX, SizeY});
}

// Note: somewhere else, the sprites X and Y are going to be set.
void RendererSystem::Update() const
{
	Clear();

	if (m_Sprites.empty())
		return;

	for (const auto& sprite : m_Sprites)
	{
		// const int targetX = sprite->GetX() + 1;
		//
		// sprite->SetPosition(targetX, sprite->GetY()); // TEMP
		Blit(*sprite);
	}

	Present();
}

//PRIVATE

SDL_Texture* RendererSystem::LoadTexture(const std::string& FilePath) const
{
	const std::string filePath = IMAGE_ROOT_PATH + FilePath;
	return IMG_LoadTexture(m_Renderer, filePath.c_str());
}

void RendererSystem::Blit(const Sprite& Sprite) const
{
	const SDL_Rect dest = Sprite.GetRect();	
	SDL_RenderCopy(m_Renderer, Sprite.GetTexture(), NULL, &dest);
}

void RendererSystem::Clear() const
{
	SDL_RenderClear(m_Renderer);
}

void RendererSystem::Present() const
{
	SDL_RenderPresent(m_Renderer);
}

