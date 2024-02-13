#include "pch.h"
#include "Sprite.h"

#include "Utils/Log.h"


Sprite::Sprite(std::weak_ptr<Texture> Texture, int X, int Y, float SizeX, float SizeY):
    m_Texture{Texture}, m_x{X}, m_y{Y},
    m_SizeX(SizeX), m_SizeY(SizeY),
    m_PixelsWidth(0), m_PixelsHeight(0)
{
    if (const auto sharedTexture = Texture.lock())
        SDL_QueryTexture(sharedTexture->GetSDLPtr(), NULL, NULL,
                         &m_PixelsWidth, &m_PixelsHeight);
}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}

void Sprite::SetPosition(int X, int Y)
{
    m_x = X;
    m_y = Y;
}

void Sprite::SetSize(int X, int Y)
{
    m_SizeX = X;
    m_SizeY = Y;
}
