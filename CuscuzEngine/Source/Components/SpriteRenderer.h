#pragma once

#include <SDL_render.h>
#include <memory>

#include "vec4.hpp"
#include "Render/IndexBuffer.h"
#include "Render/IRender.h"
#include "World/Component.h"
#include "Render/Shader.h"
#include "Render/VertexArray.h"

class Sprite;

class SpriteRenderer : public Component, public IRender
{
    float vertexPositions[20] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // vertex 0 top left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // vertex 1 top right
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // vertex 2 bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // vertex 3 bottom left
    };

    unsigned int indexBuffer[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;
    Shader m_SpriteShader;
    
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

    REGISTER_COMPONENT(SpriteRenderer);
    void ImGuiDisplayComponent() override;        
protected:
    float GetRotationDegrees() const;

private:
    bool LoadShaders();
};
