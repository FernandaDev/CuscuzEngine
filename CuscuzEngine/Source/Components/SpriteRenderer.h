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
    float m_Vertices[4 * 5] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // vertex 0 top left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // vertex 1 top right
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // vertex 2 bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // vertex 3 bottom left
    };

    unsigned int m_Indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    CC_AssetRef<VertexArray> m_VertexArray;
    CC_AssetRef<Shader> m_Shader;
    
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
    const CC_AssetRef<VertexArray>& GetVertexArray() const override { return m_VertexArray; }
    const CC_AssetRef<Shader>& GetShader() const override { return m_Shader; }

    REGISTER_COMPONENT(SpriteRenderer);
    void ImGuiDisplayComponent() override;        
protected:
    float GetRotationDegrees() const;
};
