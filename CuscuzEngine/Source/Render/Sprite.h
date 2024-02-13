#pragma once

#include "vec2.hpp"
#include "Render/Texture.h"

class Sprite
{
    std::weak_ptr<Texture> m_Texture;

    glm::vec2 m_Position;
    glm::vec2 m_Size;
    glm::vec2 m_Pivot;
    glm::i32vec2 m_PixelsDimension;
    
public:
    Sprite() = delete;
    Sprite(std::weak_ptr<Texture> Texture, glm::vec2 Position, glm::vec2 Size = {1,1});
    ~Sprite();

    void SetPosition(int X, int Y);
    void SetPosition(glm::vec2 NewPosition);
    void SetSize(int X, int Y);
    void SetSize(glm::vec2 NewSize);
    
    glm::vec2 GetPosition() const { return m_Position; }
    glm::vec2 GetSize() const { return m_Size; }
    int GetWidth() const { return m_PixelsDimension.x * m_Size.x; } //TODO review this!
    int GetHeight() const { return m_PixelsDimension.y * m_Size.y; }

    Texture* GetTexture() const
    {
        if (const auto sharedTexture = m_Texture.lock())
            return sharedTexture.get();

        return nullptr;
    }
};
