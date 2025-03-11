#include "pch.h"
#include "SubTexture2D.h"

#include "Texture.h"

namespace Cuscuz
{
    SubTexture2D::SubTexture2D(const CC_AssetRef<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) :
        m_Texture(texture)
    {
        m_TexCoords[0] = { min.x, min.y };
        m_TexCoords[1] = { max.x, min.y };
        m_TexCoords[2] = { max.x, max.y };
        m_TexCoords[3] = { min.x, max.y };
    }

    CC_AssetRef<SubTexture2D> SubTexture2D::CreateFromCoords(const CC_AssetRef<Texture2D>& texture,
        const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, float tileOffset)
    {
        const auto texWidth = static_cast<float>(texture->GetWidth());
        const auto texHeight = static_cast<float>(texture->GetHeight());

        glm::vec2 min = {
            (coords.x * (cellSize.x + tileOffset)) / texWidth ,
            (coords.y * (cellSize.y + tileOffset)) / texHeight
        };
        
        glm::vec2 max = {
            (coords.x * (cellSize.x + tileOffset) + spriteSize.x * cellSize.x) / texWidth,
            (coords.y * (cellSize.y + tileOffset) + spriteSize.y * cellSize.y) / texHeight
        };
        
        return CreateAssetRef<SubTexture2D>(texture, min, max);
    }
}
