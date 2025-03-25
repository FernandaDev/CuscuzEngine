#include "pch.h"

#include "SpriteRenderer.h"
#include "gtc/matrix_transform.hpp"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/World/Actor.h"
#include "Cuscuz/Render/Renderer2D.h"
#include "Cuscuz/World/Scene.h"
#include "Proxys/SpriteRendererProxy.h"

namespace Cuscuz
{
    SpriteRenderer::SpriteRenderer(int drawOrder) :
    m_DrawOrder(drawOrder), m_Color(1.f, 1.f, 1.f, 1)
    { }

    void SpriteRenderer::OnAdded()
    {
        Scene::GetOnDrawableProxyAddedEvent().Broadcast(this); //TODO create and pass the proxy
    }

    void SpriteRenderer::OnRemoved()
    {
        Scene::GetOnDrawableProxyRemovedEvent().Broadcast(this);
    }

    void SpriteRenderer::Draw()
    {
        const auto transform = m_OwnerActor->GetTransform().GetWorldTransform();

        if(!m_Sprite)
            Renderer2D::DrawQuad(transform, m_Color);
        else
        {
            if(const auto texture = m_Sprite->GetTexture())
                Renderer2D::DrawQuad(transform, m_Color, texture);
            else
                Renderer2D::DrawQuad(transform, m_Color);
        }
    }

    void SpriteRenderer::SetSprite(const CC_AssetRef<Sprite>& newSprite)
    {
        m_Sprite = newSprite;
    }

    void SpriteRenderer::SetDrawOrder(uint32_t drawOrder)
    {
        m_DrawOrder = drawOrder;
    }

    void SpriteRenderer::SetColor(glm::vec4 color)
    {
        m_Color = color;
    }

    uint32_t SpriteRenderer::GetTexHeight() const
    {
        if (m_Sprite)
            return m_Sprite->GetHeight();

        LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
        return 0;
    }

    uint32_t SpriteRenderer::GetTextWidth() const
    {
        if (m_Sprite)
            return m_Sprite->GetHeight();

        LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
        return 0;
    }

    float SpriteRenderer::GetRotationDegrees() const
    {
        return glm::degrees(m_OwnerActor->GetTransform().GetRotation());
    }
}
