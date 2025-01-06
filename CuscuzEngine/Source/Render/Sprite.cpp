#include "pch.h"
#include "Sprite.h"

#include "Render/Texture.h"
#include "Utils/Log.h"

Sprite::Sprite() : m_Width(0), m_Height(0), m_Pivot(0, 0)
{}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}

void Sprite::SetTexture(const CC_AssetRef<Texture2D>& texture)
{
    m_Texture = texture;

    m_Width = m_Texture->GetWidth();
    m_Height = m_Texture->GetHeight();
}

void Sprite::BindTexture() const
{
    m_Texture->Bind();
}
