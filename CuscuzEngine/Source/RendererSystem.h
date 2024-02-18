#pragma once

#include "pch.h"
#include "Render/Sprite.h"
#include "SDL.h"

class SpriteComponent;

class RendererSystem
{
 	SDL_Renderer* m_Renderer;
	std::vector<std::weak_ptr<SpriteComponent>> m_SpriteComponents;

public:
	RendererSystem() = delete;
	RendererSystem(class Window* Window);
	~RendererSystem();

	SDL_Renderer* GetRenderer() const { return m_Renderer; }

	void AddSpriteComponent(std::shared_ptr<SpriteComponent> SpriteComponent);
	void RemoveSpriteComponent(std::shared_ptr<SpriteComponent> SpriteComponent);

	void Update() const;
	void Render() const;
	
private:
	void Blit(const Sprite& Sprite) const;
	void Clear() const;
};

