#pragma once

#include "Render/Texture.h"

class Sprite
{
    std::weak_ptr<Texture> m_Texture;

    int m_x;
    int m_y;
    int m_SizeX;
    int m_SizeY;
    int m_OriginalWidth;
    int m_OriginalHeight;
    
public:
    Sprite() = delete;
    Sprite(std::weak_ptr<Texture> Texture, int X, int Y, int SizeX = 1, int SizeY = 1);
    ~Sprite();

    void SetPosition(int X, int Y);
    void SetSize(int X, int Y);
    
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetSizeX() const { return m_SizeX; }
    int GetSizeY() const { return m_SizeY; }
    int GetWidth() const { return m_OriginalWidth * m_SizeX; }
    int GetHeight() const { return m_OriginalHeight * m_SizeY; }

    Texture* GetTexture() const
    {
        if (const auto sharedTexture = m_Texture.lock())
            return sharedTexture.get();

        return nullptr;
    }
};
