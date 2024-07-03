#include "pch.h"
#include "Sprite.h"
#include "Utils/Log.h"

Sprite::Sprite(std::weak_ptr<Texture> texture) :
    m_Texture{texture}, m_PixelsDimension(0,0), m_Pivot(0,0)
{
    if (const auto sharedTexture = texture.lock())
        SDL_QueryTexture(sharedTexture->SDLPtr(), NULL, NULL,
                         &m_PixelsDimension.x, &m_PixelsDimension.y);
}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}