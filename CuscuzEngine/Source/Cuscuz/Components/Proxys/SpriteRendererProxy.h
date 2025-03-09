#pragma once
#include "vec4.hpp"
#include "mat4x4.hpp"
#include "Cuscuz/Components/SpriteRenderer.h"
#include "Cuscuz/Core/Core.h"
#include "Cuscuz/Render/IDrawable.h"

namespace Cuscuz
{
    class Texture2D;

    class SpriteRendererProxy : public IDrawable
    {
        glm::mat4 m_WorldTransform = {};
        glm::vec4 m_Color = {};
        CC_AssetRef<Texture2D> m_Texture = {};
        uint32_t m_DrawOrder = 0;
    
    public:
        SpriteRendererProxy(SpriteRenderer* spriteRenderer);
        virtual ~SpriteRendererProxy() = default;
        
        void Draw() override;
        uint32_t GetDrawOrder() const override { return m_DrawOrder; }

        //friend SpriteRenderer;
    };
}
