#pragma once

#include <SDL_render.h>
#include <memory>

#include "vec4.hpp"
#include "Render/IRender.h"
#include "World/Component.h"

class Sprite;
class Shader;
class VertexArray;

class SpriteComponent : public Component, public IRender
{
    float vertexBuffer[12] = {
        -0.5f, 0.5f, 0.0f,  //vertex 0
         0.5f, 0.5f, 0.0f,  //vertex 1
         0.5f,-0.5f, 0.0f,  //vertex 2
        -0.5f,-0.5f, 0.0f   //vertex 3
    };

    unsigned int indexBuffer[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray* m_SpriteVerts;
    Shader* m_SpriteShader;
    //Material
    
protected:
    int m_DrawOrder = 0;
    glm::vec4 m_Color = {};
    std::weak_ptr<Sprite> m_Sprite {};

public:
    SpriteComponent(int drawOrder = 0);
    ~SpriteComponent() override = default;

    void Draw() override;
    void SetSprite(std::weak_ptr<Sprite> newSprite);

    void SetDrawOrder(int drawOrder);

    int GetDrawOrder() const override { return m_DrawOrder; }
    int GetTexHeight() const;
    int GetTextWidth() const;

    REGISTER_COMPONENT(SpriteComponent);

protected:
    //SDL_Rect GetDestination(const std::shared_ptr<Sprite>& sprite) const;
    float GetRotationDegrees() const;

private:
    bool LoadShaders();
};
