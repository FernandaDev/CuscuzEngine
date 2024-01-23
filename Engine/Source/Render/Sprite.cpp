#include "pch.h"
#include "Sprite.h"


Sprite::Sprite(SDL_Texture* Texture, int X, int Y, int SizeX, int SizeY):
m_Texture{Texture}, m_x{X}, m_y{Y},
m_SizeX(SizeX), m_SizeY(SizeY),
m_OriginalWidth(0), m_OriginalHeight(0)
{
    if(Texture)
        SDL_QueryTexture(Texture, NULL, NULL, &m_OriginalWidth, &m_OriginalHeight);    
}

Sprite::~Sprite()
{
    if(m_Texture)
        SDL_DestroyTexture(m_Texture);
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
