#pragma once

#include "vec2.hpp"
#include "Render/Texture.h"

class Sprite
{
    std::weak_ptr<Texture> m_Texture;
    glm::i32vec2 m_PixelsDimension;
    glm::vec2 m_Pivot;
    
public:
    Sprite() = delete;
    Sprite(std::weak_ptr<Texture> texture);
    ~Sprite();

    int GetWidth() const { return m_PixelsDimension.x; }
    int GetHeight() const { return m_PixelsDimension.y; }

    Texture* GetTexture() const
    {
        if (const auto sharedTexture = m_Texture.lock())
            return sharedTexture.get();

        return nullptr;
    }
};
