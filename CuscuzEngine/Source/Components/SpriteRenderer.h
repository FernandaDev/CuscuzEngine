#pragma once

#include <SDL_render.h>
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
    
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<Shader> m_Shader;
    
protected:
    int m_DrawOrder = 0;
    glm::vec4 m_Color = {};
    Sprite* m_Sprite {};

public:
    SpriteRenderer(int drawOrder = 0);
    ~SpriteRenderer() override = default;

    void Draw() override;
    void SetSprite(Sprite* newSprite);
    Sprite* GetSprite() const { return m_Sprite; }

    void SetDrawOrder(int drawOrder);

    int GetDrawOrder() const override { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;
    const std::shared_ptr<VertexArray>& GetVertexArray() const override { return m_VertexArray; }
    const std::shared_ptr<Shader>& GetShader() const override { return m_Shader; }

    REGISTER_COMPONENT(SpriteRenderer);
    void ImGuiDisplayComponent() override;        
protected:
    float GetRotationDegrees() const;
};
