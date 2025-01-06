#pragma once

#include "vec2.hpp"
#include "Core/CC_Core.h"

class Texture2D;

class Sprite
{
    CC_AssetRef<Texture2D> m_Texture{};
    uint32_t m_Width, m_Height;
    glm::vec2 m_Pivot;
    
public:
    Sprite();
    ~Sprite();

    void SetTexture(const CC_AssetRef<Texture2D>& texture);
    const CC_AssetRef<Texture2D>& GetTexture() const { return m_Texture; }

    void BindTexture() const;

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    float GetWidthF() const { return static_cast<float>(m_Width); }
    float GetHeightF() const { return static_cast<float>(m_Height); }

};
