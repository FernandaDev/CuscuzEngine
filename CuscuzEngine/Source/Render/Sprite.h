#pragma once

#include "Render/Texture.h"

class Sprite
{
    std::weak_ptr<Texture> m_Texture;

    int m_x;
    int m_y;
    float m_SizeX;
    float m_SizeY;
    int m_PixelsWidth;
    int m_PixelsHeight;

    //Vec2 m_Pivot;
    
public:
    Sprite() = delete;
    Sprite(std::weak_ptr<Texture> Texture, int X, int Y, float SizeX = 1, float SizeY = 1);
    ~Sprite();

    void SetPosition(int X, int Y);
    void SetSize(int X, int Y);
    
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    float GetSizeX() const { return m_SizeX; }
    float GetSizeY() const { return m_SizeY; }
    int GetWidth() const { return m_PixelsWidth * m_SizeX; }
    int GetHeight() const { return m_PixelsHeight * m_SizeY; }

    Texture* GetTexture() const
    {
        if (const auto sharedTexture = m_Texture.lock())
            return sharedTexture.get();

        return nullptr;
    }
};
