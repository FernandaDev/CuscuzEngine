#pragma once

#include <SDL_render.h>
#include <memory>

#include "vec4.hpp"
#include "Render/IRender.h"
#include "World/Component.h"

class Sprite;

class SpriteComponent : public Component, public IRender
{
protected:
    int m_DrawOrder = 0;
    SDL_BlendMode m_BlendMode = SDL_BLENDMODE_NONE;
    glm::vec4 m_Color = {};
    std::weak_ptr<Sprite> m_Sprite {};

public:
    SpriteComponent(int drawOrder = 0, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE);
    ~SpriteComponent() override = default;

    void Draw(SDL_Renderer* renderer) override;
    void SetSprite(std::weak_ptr<Sprite> newSprite);

    void SetDrawOrder(int drawOrder);
    void SetBlendMode(SDL_BlendMode blendMode);

    int GetDrawOrder() const override { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;

    REGISTER_COMPONENT(SpriteComponent);

protected:
    //SDL_Rect GetDestination(const std::shared_ptr<Sprite>& sprite) const;
    float GetRotationDegrees() const;
};
