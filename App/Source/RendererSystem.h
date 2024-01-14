#pragma once

#include <vector>
#include <memory>
#include "Render/Sprite.h"
#include "SDL.h"

class RendererSystem
{
	SDL_Renderer* m_Renderer;
	std::vector<std::shared_ptr<Sprite>> m_Sprites;

public:
	RendererSystem() = delete;
	RendererSystem(class Window* Window);
	~RendererSystem();

	SDL_Renderer* GetRenderer() const { return m_Renderer; }

	void CreateSprite(const std::string& FilePath);
	void CreateSprite(const std::string& FilePath, int X, int Y);
	void CreateSprite(const std::string& FilePath, int X, int Y, int SizeX, int SizeY);
	void Update() const;
	
private:
	SDL_Texture* LoadTexture(const std::string& FilePath) const;
	void Blit(const Sprite& Sprite) const;
	void Present() const;
	void Clear() const;
};

