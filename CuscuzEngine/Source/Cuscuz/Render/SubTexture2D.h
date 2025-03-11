#pragma once
#include "vec2.hpp"
#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    class Texture2D;
    
    class SubTexture2D
    {
        CC_AssetRef<Texture2D> m_Texture;
        glm::vec2 m_TexCoords[4];
        
    public:
        SubTexture2D(const CC_AssetRef<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

        static CC_AssetRef<SubTexture2D> CreateFromCoords(const CC_AssetRef<Texture2D>& texture, const glm::vec2& coords,
            const glm::vec2& cellSize, const glm::vec2& spriteSize = {1 ,1}, float tileOffset = 0);

        const CC_AssetRef<Texture2D>& GetTexture() const { return m_Texture; }
        const glm::vec2* GetTexCoords() const { return m_TexCoords; }
    };
}
