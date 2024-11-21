#include "pch.h"
#include "Sprite.h"
#include "Utils/Log.h"

Sprite::Sprite() : m_PixelsDimension(0,0), m_Pivot(0,0)
{}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}

void Sprite::SetTexture(const std::weak_ptr<Texture>& texture)
{
    m_Texture = texture;

    if(const auto tex = m_Texture.lock())
    {
        m_PixelsDimension.x = tex->GetWidth();
        m_PixelsDimension.y = tex->GetHeight();
    }
}

void Sprite::BindTexture() const
{
    if(const auto tex = m_Texture.lock())
        tex->SetActive();
}
