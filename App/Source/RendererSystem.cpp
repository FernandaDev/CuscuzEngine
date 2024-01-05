#include <iostream>

#include "RendererSystem.h"
#include "Window.h"
#include "SDL_image.h"

#define IMAGE_ROOT_PATH "Source/Assets/Images/"
#define MAX_TEXTURE_AMOUNT 24

RendererSystem::RendererSystem(Window* Window):
	m_Renderer{nullptr}
{
	m_Renderer = SDL_CreateRenderer(Window->GetWindow(), -1, 0);

	if (!m_Renderer)
		std::cout << "Could not create a renderer." << std::endl;

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	
	m_Textures.reserve(MAX_TEXTURE_AMOUNT);
}

RendererSystem::~RendererSystem()
{
	if(m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
}

SDL_Texture* RendererSystem::LoadTexture(std::string FilePath)
{
	std::string filePath = IMAGE_ROOT_PATH + FilePath;
	return IMG_LoadTexture(m_Renderer, filePath.c_str());
}

void RendererSystem::AddTexture(std::string FilePath)
{
	if (m_Textures.size() >= MAX_TEXTURE_AMOUNT)
	{
		std::cout << "Cannot load more textures!" << std::endl;
		return;
	}

	auto newTexture = LoadTexture(FilePath);

	if (!newTexture)
	{
		std::cout << "Couldn't load the texture!" << std::endl;
		return;
	}

	m_Textures.push_back(newTexture);
}

void RendererSystem::Update()
{
	Clear();

	if (m_Textures.size() <= 0)
		return;

	for (int i = 0; i < m_Textures.size(); i++)
	{
		Blit(m_Textures[i], i * 64, 0);
	}

	Present();
}

void RendererSystem::Blit(SDL_Texture* Texture, int X, int Y)
{
	SDL_Rect dest;

	dest.x = X;
	dest.y = Y;
	SDL_QueryTexture(Texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(m_Renderer, Texture, NULL, &dest);
}

void RendererSystem::Clear()
{
	SDL_RenderClear(m_Renderer);
}

void RendererSystem::Present()
{
	SDL_RenderPresent(m_Renderer);
}

