#include "pch.h"

#include "Animation2DComponent.h"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    CREATE_COMPONENT_REGISTRY(Animation2DComponent)

    Animation2DComponent::Animation2DComponent(int frameCount, int drawOrder) :
    SpriteRenderer(drawOrder), m_FrameCount(frameCount), m_AnimFPS(10), m_CurrentFrame(0)
    {}

    void Animation2DComponent::Update(float deltaTime)
    {    
        PlayFrame(0,0);

        m_CurrentFrame += m_AnimFPS * deltaTime;
    
        while(m_CurrentFrame >= m_FrameCount)
        {
            m_CurrentFrame -= m_FrameCount;
        }
    }

    void Animation2DComponent::Draw()
    {
        // const auto sprite = m_Sprite.lock();
        // if(!sprite || !sprite->GetTexture())
        //     return;
        //
        // SDL_Rect dest;
        // dest.w = m_SingleSpriteSize.x;
        // dest.h = m_SingleSpriteSize.y;
        // dest.x = static_cast<int>(m_OwnerActor->GetPosition().x);
        // dest.y = static_cast<int>(m_OwnerActor->GetPosition().y);
        //
        // SDL_RenderCopyEx(renderer, sprite->GetTexture()->SDLPtr(),
        // &m_Source, &dest, -GetRotationDegrees(), nullptr, SDL_FLIP_NONE);
    }

    void Animation2DComponent::PlayFrame(int x, int y)
    {
        m_Source.w = m_SingleSpriteSize.x;
        m_Source.h = m_SingleSpriteSize.y;
    
        m_Source.y = y;
        m_Source.x = x + m_Source.w * static_cast<int>(m_CurrentFrame);
    }
}