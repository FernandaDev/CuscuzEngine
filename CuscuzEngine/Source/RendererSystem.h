#pragma once

#include "pch.h"
#include "Render/Sprite.h"
#include "SDL.h"

class IRender;
class SpriteComponent;

class RendererSystem
{
 	SDL_Renderer* m_Renderer;
	std::vector<std::weak_ptr<IRender>> m_RenderComponents;

public:
	RendererSystem() = delete;
	RendererSystem(class Window* window);
	~RendererSystem();

	SDL_Renderer* GetRenderer() const { return m_Renderer; }

	void AddRenderComponent(std::shared_ptr<IRender> spriteComponent);
	void RemoveRenderComponent(std::shared_ptr<IRender> renderComponent);

	void Update();
	void Render() const;
	
private:
	void Blit(const Sprite& sprite) const;
	void Clear() const;
};

