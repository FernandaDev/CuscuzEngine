#pragma once
#include <SDL_render.h>

#include "World/Component.h"

class Sprite;

class SpriteComponent : public Component
{
protected:
    std::weak_ptr<Sprite> m_sprite;
    int m_DrawOrder;
    
public:
    SpriteComponent(int DrawOrder = 100) :
    m_DrawOrder(DrawOrder){}
    ~SpriteComponent() override = default;

    virtual void Draw(SDL_Renderer* Renderer);
    virtual void SetSprite(std::shared_ptr<Sprite> NewSprite);

    int GetDrawOrder() const { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;
};
