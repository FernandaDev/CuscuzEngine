#include "pch.h"
#include "SpriteComponent.h"

#include <utility>

#include "detail/func_trigonometric.inl"
#include "Render/Sprite.h"
#include "World/Actor.h"

CREATE_COMPONENT_REGISTRY(SpriteComponent);

SpriteComponent::SpriteComponent(int drawOrder, SDL_BlendMode blendMode) :
m_DrawOrder(drawOrder), m_BlendMode(blendMode), m_Color(0,0,0,1)
{}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    const auto sprite = m_Sprite.lock();
    if(!sprite || !sprite->GetTexture())
        return;

    SDL_Rect dest;
    dest.w = static_cast<int>(sprite->GetWidth() * m_OwnerActor->GetScale());
    dest.h = static_cast<int>(sprite->GetHeight() * m_OwnerActor->GetScale());
    dest.x = static_cast<int>(m_OwnerActor->GetPosition().x - dest.w * 0.5);
    dest.y = static_cast<int>(m_OwnerActor->GetPosition().y - dest.h * 0.5);

    SDL_RenderCopyEx(renderer, sprite->GetTexture()->SDLPtr(),
        nullptr, &dest, -GetRotationDegrees(), nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetSprite(std::weak_ptr<Sprite> newSprite)
{
    m_Sprite = std::move(newSprite);
}

void SpriteComponent::SetDrawOrder(int drawOrder)
{
    m_DrawOrder = drawOrder;
}

void SpriteComponent::SetBlendMode(SDL_BlendMode blendMode)
{
    m_BlendMode = blendMode;
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

float SpriteComponent::GetRotationDegrees() const
{
    return glm::degrees(m_OwnerActor->GetRotation());
}
