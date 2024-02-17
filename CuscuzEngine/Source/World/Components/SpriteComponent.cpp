﻿#include "pch.h"
#include "SpriteComponent.h"

#include <utility>

#include "../../../../App/Source/Application.h"
#include "detail/func_trigonometric.inl"
#include "Events/EventHandler.h"
#include "Render/Sprite.h"

SpriteComponent::SpriteComponent(glm::vec2 Size, int DrawOrder, SDL_BlendMode BlendMode) :
m_Size(Size), m_DrawOrder(DrawOrder), m_BlendMode(BlendMode), m_Color(0,0,0,1)
{}

SpriteComponent::~SpriteComponent()
{
    LOG_INFO("Sprite component destroyed.");
}

void SpriteComponent::Draw(SDL_Renderer* Renderer)
{
    const auto sprite = m_Sprite.lock();
    if(!sprite || !sprite->GetTexture())
        return;

    SDL_Rect dest;
    dest.w = static_cast<int>(sprite->GetWidth() * m_OwnerActor->GetScale());
    dest.h = static_cast<int>(sprite->GetHeight() * m_OwnerActor->GetScale());
    dest.x = static_cast<int>(m_OwnerActor->GetPosition().x - dest.w * 0.5);
    dest.y = static_cast<int>(m_OwnerActor->GetPosition().x - dest.h * 0.5);

    const auto rotation = glm::degrees(m_OwnerActor->GetRotation());
    
    SDL_RenderCopyEx(Renderer, sprite->GetTexture()->SDLPtr(),
        nullptr, &dest, -rotation, nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetSprite(std::weak_ptr<Sprite> NewSprite)
{
    m_Sprite = std::move(NewSprite);
}

void SpriteComponent::SetSize(int X, int Y)
{
    m_Size = glm::vec2(X,Y);
}

void SpriteComponent::SetDrawOrder(int DrawOrder)
{
    m_DrawOrder = DrawOrder;
}

void SpriteComponent::SetBlendMode(SDL_BlendMode BlendMode)
{
    m_BlendMode = BlendMode;
}

int SpriteComponent::GetTexHeight() const
{
    if(const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
    return 0;
}

int SpriteComponent::GetTextWidth() const
{
    if(const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
    return 0;
}
