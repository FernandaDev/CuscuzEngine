#pragma once

#include <memory>
#include "vec4.hpp"
#include "Cuscuz/Render/IRender.h"
#include "Cuscuz/World/Component.h"
#include "Cuscuz/Render/Shader.h"
#include "Cuscuz/Render/VertexArray.h"

namespace Cuscuz
{
    class Sprite;
    
    class SpriteRenderer : public Component, public IRender
    {
    protected:
        int m_DrawOrder = 0;
        glm::vec4 m_Color = {};
        CC_AssetRef<Sprite> m_Sprite {};

    public:
        SpriteRenderer(int drawOrder = 0);
        ~SpriteRenderer() override;

        void Draw() override;
        void SetSprite(const CC_AssetRef<Sprite>& newSprite);
        const CC_AssetRef<Sprite>& GetSprite() const { return m_Sprite; }

        void SetDrawOrder(int drawOrder);
        void SetColor(glm::vec4 color);

        int GetDrawOrder() const override { return m_DrawOrder; }
        int GetTexHeight() const;
        int GetTextWidth() const;

        REGISTER_COMPONENT(SpriteRenderer);
        //void ImGuiDisplayComponent() override;        
    protected:
        float GetRotationDegrees() const;
    };
}