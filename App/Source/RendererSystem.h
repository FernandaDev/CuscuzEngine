#pragma once

#include <vector>
#include "SDL.h"

class RendererSystem
{
	SDL_Renderer* m_Renderer;
	std::vector<SDL_Texture*> m_Textures;

public:
	RendererSystem() = delete;
	RendererSystem(class Window* Window);
	~RendererSystem();

	SDL_Renderer* GetRenderer() const { return m_Renderer; }
	SDL_Texture* LoadTexture(std::string FilePath);

	void AddTexture(std::string FilePath);
	void Update();
	
private:
	void Blit(SDL_Texture* Texture, int X, int Y);
	void Present();
	void Clear();
};

