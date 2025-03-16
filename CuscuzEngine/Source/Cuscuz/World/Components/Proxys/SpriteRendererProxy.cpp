#include "pch.h"

#include "SpriteRendererProxy.h"
#include "Cuscuz/Render/Renderer2D.h"
#include "Cuscuz/Render/Sprite.h"

Cuscuz::SpriteRendererProxy::SpriteRendererProxy(SpriteRenderer* spriteRenderer)
{
    m_WorldTransform = spriteRenderer->GetTransform().GetWorldTransform();
    m_Color = spriteRenderer->GetColor();
    m_DrawOrder = spriteRenderer->GetDrawOrder();
    m_Texture = spriteRenderer->GetSprite()->GetTexture();
}

void Cuscuz::SpriteRendererProxy::Draw()
{
    if(m_Texture != nullptr)
    {
        Renderer2D::DrawQuad(m_WorldTransform, m_Color, m_Texture);
    }
    else
    {
        Renderer2D::DrawQuad(m_WorldTransform, m_Color);
    }
}
