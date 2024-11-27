#include "pch.h"
#include "Sprite.h"

#include "Render/Texture.h"
#include "Utils/Log.h"

Sprite::Sprite() : m_PixelsDimension(0, 0), m_Pivot(0, 0)
{}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}

void Sprite::SetTexture(Texture* texture)
{
    m_Texture = texture;

    m_PixelsDimension.x = m_Texture->GetWidth();
    m_PixelsDimension.y = m_Texture->GetHeight();
}

void Sprite::BindTexture() const
{
    m_Texture->SetActive();
}
