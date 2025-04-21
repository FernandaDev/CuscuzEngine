#pragma once

#include "Cuscuz.h"

namespace Cuscuz
{
    struct Tile
    {
        glm::mat4 Transform;
        CC_AssetRef<SubTexture2D> SubTexture;

        Tile(const CC_AssetRef<SubTexture2D>& subTexture, glm::mat4 transform):
        Transform(transform), SubTexture(subTexture) { }

        const glm::vec3& GetPos() { return { Transform[3] }; }
    };

    std::vector<Tile> gTiles;

    static void DrawRandomMap()
    {
        CC_AssetRef<Texture2D> m_Spritesheet = Texture2D::Create("Assets/Images/Map_SpriteSheet.png");
        std::array<CC_AssetRef<SubTexture2D>, 3> m_MapTiles; // grass 5,29 | water 3,29 | dirt 6,29  
        
        m_MapTiles[0] = SubTexture2D::CreateFromCoords(m_Spritesheet, {5, 29}, {16,16}, {1,1}, 1.f);
        m_MapTiles[1] = SubTexture2D::CreateFromCoords(m_Spritesheet, {3, 29}, {16,16}, {1,1}, 1.f);
        m_MapTiles[2] = SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 29}, {16,16}, {1,1}, 1.f);
        
        const glm::ivec2& gridSize = {25,25};

        gTiles.clear();
        gTiles.reserve(gridSize.x * gridSize.y);
    
        Random& random = Random::Get();
        float halfGridX = gridSize.x * 0.5f;
        float halfGridY = gridSize.y * 0.5f;
        
        for (int x = 0; x < gridSize.x; ++x)
        {
            for (int y = 0; y < gridSize.y; ++y)
            {
                auto pos = glm::vec3(x - halfGridX , y - halfGridY, -0.1f);
                //LOG_INFO("Pos: {0}, {1}", pos.x, pos.y);
                const auto randomIndex = random.GetRandomNumber(0, m_MapTiles.size() - 1);
                std::shared_ptr<SubTexture2D>& tile = m_MapTiles[randomIndex];
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
                gTiles.emplace_back(tile, transform);
            }
        }
    }
}