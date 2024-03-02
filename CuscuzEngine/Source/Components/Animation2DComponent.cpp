#include "pch.h"
#include "Animation2DComponent.h"

#include "Render/Sprite.h"
#include "World/Actor.h"

Animation2DComponent::Animation2DComponent(int FrameCount, int DrawOrder, SDL_BlendMode BlendMode) :
SpriteComponent(DrawOrder, BlendMode), m_FrameCount(FrameCount), m_AnimFPS(10), m_CurrentFrame(0)
{
    m_Name = "Animation2DComponent";
}

void Animation2DComponent::Update(float DeltaTime)
{    
    PlayFrame(0,0);

    m_CurrentFrame += m_AnimFPS * DeltaTime;

    while(m_CurrentFrame >= m_FrameCount)
    {
        m_CurrentFrame -= m_FrameCount;
    }
}

void Animation2DComponent::Draw(SDL_Renderer* Renderer)
{
    const auto sprite = m_Sprite.lock();
    if(!sprite || !sprite->GetTexture())
        return;

    SDL_Rect dest;
    dest.w = m_SingleSpriteSize.x;
    dest.h = m_SingleSpriteSize.y;
    dest.x = static_cast<int>(m_OwnerActor->GetPosition().x);
    dest.y = static_cast<int>(m_OwnerActor->GetPosition().y);
    
    SDL_RenderCopyEx(Renderer, sprite->GetTexture()->SDLPtr(),
    &m_Source, &dest, -GetRotationDegrees(), nullptr, SDL_FLIP_NONE);
}

void Animation2DComponent::PlayFrame(int X, int Y)
{
    m_Source.w = m_SingleSpriteSize.x;
    m_Source.h = m_SingleSpriteSize.y;
    
    m_Source.y = Y;
    m_Source.x = X + m_Source.w * static_cast<int>(m_CurrentFrame);
}
