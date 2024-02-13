#include "pch.h"
#include "Sprite.h"

#include "Utils/Log.h"


Sprite::Sprite(std::weak_ptr<Texture> Texture, glm::vec2 Position, glm::vec2 Size) :
    m_Texture{Texture}, m_Position{Position}, m_Size(Size), m_PixelsDimension(0,0)
{
    if (const auto sharedTexture = Texture.lock())
        SDL_QueryTexture(sharedTexture->GetSDLPtr(), NULL, NULL,
                         &m_PixelsDimension.x, &m_PixelsDimension.y);
}

Sprite::~Sprite()
{
    LOG_INFO("Sprite Destroyed!");
}

void Sprite::SetPosition(int X, int Y)
{
    m_Position.x = X;
    m_Position.y = Y;
}

void Sprite::SetPosition(glm::vec2 NewPosition)
{
    m_Position = NewPosition;
}

void Sprite::SetSize(int X, int Y)
{
    m_Size.x = X;
    m_Size.y = Y;
}

void Sprite::SetSize(glm::vec2 NewSize)
{
    m_Size = NewSize;
}