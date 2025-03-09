#pragma once

#include <memory>
#include "vec4.hpp"
#include "Cuscuz/Render/IDrawable.h"
#include "Cuscuz/World/Component.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    class Sprite;
    
    class SpriteRenderer : public Component, public IDrawable
    {
    protected:
        uint32_t m_DrawOrder = 0;
        glm::vec4 m_Color = {};
        CC_AssetRef<Sprite> m_Sprite {};
        //SpriteRendererProxy* m_Proxy{};

    public:
        SpriteRenderer(int drawOrder = 0);
        ~SpriteRenderer() override = default;

        void OnAdded() override;
        void OnRemoved() override;
        
        void SetSprite(const CC_AssetRef<Sprite>& newSprite);
        const CC_AssetRef<Sprite>& GetSprite() const { return m_Sprite; }

        void SetDrawOrder(uint32_t drawOrder);
        void SetColor(glm::vec4 color);

        TransformComponent& GetTransform() const { return m_OwnerActor->GetTransform(); }
        const glm::vec4& GetColor() const { return m_Color; }

        uint32_t GetDrawOrder() const override { return m_DrawOrder; }
        uint32_t GetTexHeight() const;
        uint32_t GetTextWidth() const;

        REGISTER_COMPONENT(SpriteRenderer);
        //void ImGuiDisplayComponent() override;        
    protected:
        void Draw() override;
        float GetRotationDegrees() const;
    };
}
