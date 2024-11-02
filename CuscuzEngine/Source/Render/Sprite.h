#pragma once


#include "vec2.hpp"
#include "Render/Texture.h"

class Sprite
{
    std::weak_ptr<Texture> m_Texture;
    glm::i32vec2 m_PixelsDimension;
    glm::vec2 m_Pivot;
    
public:
    Sprite();
    ~Sprite();

    void SetTexture(const std::weak_ptr<Texture>& texture);
    void ActivateTexture() const;

    int GetWidth() const { return m_PixelsDimension.x; }
    int GetHeight() const { return m_PixelsDimension.y; }
    float GetWidthF() const { return static_cast<float>(m_PixelsDimension.x); }
    float GetHeightF() const { return static_cast<float>(m_PixelsDimension.y); }

};
