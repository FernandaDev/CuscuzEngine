﻿#pragma once

#include <SDL_render.h>

#include "vec2.hpp"
#include "vec4.hpp"
#include "Render/IRender.h"
#include "World/Component.h"

class Sprite;

class SpriteComponent : public Component, public IRender
{
protected:
    int m_DrawOrder;
    SDL_BlendMode m_BlendMode;
    glm::vec4 m_Color;
    std::weak_ptr<Sprite> m_Sprite;

public:
    SpriteComponent(int DrawOrder = 0, SDL_BlendMode BlendMode = SDL_BLENDMODE_NONE);
    ~SpriteComponent() override = default;

    void Draw(SDL_Renderer* Renderer) override;
    void SetSprite(std::weak_ptr<Sprite> NewSprite);

    void SetDrawOrder(int DrawOrder);
    void SetBlendMode(SDL_BlendMode BlendMode);

    int GetDrawOrder() const override { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;
protected:
    SDL_Rect GetDestination(const std::shared_ptr<Sprite>& Sprite) const;
    float GetRotationDegrees() const;
};
