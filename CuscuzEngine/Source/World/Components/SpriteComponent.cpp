#include "pch.h"
#include "SpriteComponent.h"

#include "Render/Sprite.h"

void SpriteComponent::Draw(SDL_Renderer* Renderer)
{
}

void SpriteComponent::SetSprite(std::shared_ptr<Sprite> NewSprite)
{
    m_sprite = NewSprite;
}

int SpriteComponent::GetTexHeight() const
{
    if(const auto SharedSprite = m_sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
    return 0;
}

int SpriteComponent::GetTextWidth() const
{
    if(const auto SharedSprite = m_sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
    return 0;
}
