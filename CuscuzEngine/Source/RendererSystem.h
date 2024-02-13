#pragma once

#include "pch.h"
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

	std::shared_ptr<Sprite> CreateSprite(const std::string& FilePath);
	std::shared_ptr<Sprite> CreateSprite(const std::string& FilePath, int X, int Y);
	std::shared_ptr<Sprite> CreateSprite(const std::string& FilePath, int X, int Y, float SizeX, float SizeY);
	void Update() const;
	void Render() const;
	
private:
	void Blit(const Sprite& Sprite) const;
	void Clear() const;
};

