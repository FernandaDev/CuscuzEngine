#pragma once

#include <memory>

#include "vec4.hpp"
#include "Render/IRender.h"
#include "World/Component.h"
#include "Render/Shader.h"
#include "Render/VertexArray.h"

class Sprite;

class SpriteRenderer : public Component, public IRender
{
protected:
    int m_DrawOrder = 0;
    glm::vec4 m_Color = {};
    CC_AssetRef<Sprite> m_Sprite {};

public:
    SpriteRenderer(int drawOrder = 0);
    ~SpriteRenderer() override = default;

    void Draw() override;
    void SetSprite(const CC_AssetRef<Sprite>& newSprite);
    const CC_AssetRef<Sprite>& GetSprite() const { return m_Sprite; }

    void SetDrawOrder(int drawOrder);
    void SetColor(glm::vec4 color);

    int GetDrawOrder() const override { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;

    REGISTER_COMPONENT(SpriteRenderer);
    void ImGuiDisplayComponent() override;        
protected:
    float GetRotationDegrees() const;
};
