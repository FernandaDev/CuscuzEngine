#include "pch.h"
#include "SpriteRenderer.h"

#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "Render/Sprite.h"
#include "World/Actor.h"
#include "GL/glew.h"
#include "Platform/OpenGL/GLUtils.h"
#include "Render/VertexBufferLayout.h"

CREATE_COMPONENT_REGISTRY(SpriteRenderer);

SpriteRenderer::SpriteRenderer(int drawOrder) :
    m_VertexBuffer(vertexPositions, 4 * 5 * sizeof(float)),
    m_IndexBuffer(indexBuffer, 6),
    m_DrawOrder(drawOrder), m_Color(0, 0, 0, 1)
{
    VertexBufferLayout layout;
    layout.Push<float>(3); // position
    layout.Push<float>(2); // uv
    m_VertexArray.AddBuffer(m_VertexBuffer, layout);
    
    LoadShaders();
}

bool SpriteRenderer::LoadShaders()
{
    if (!m_SpriteShader.Load("Assets/Shaders/Sprite.glsl"))
        return false;

    m_SpriteShader.Bind();

    const auto viewProj = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH),
                                                     0.0f,static_cast<float>(SCREEN_HEIGHT),
                                               -1.0f, 1.0f);
    m_SpriteShader.SetUniformM4("uViewProjection", viewProj);

    return true;
}

void SpriteRenderer::Draw()
{
    m_VertexArray.Bind();
    m_IndexBuffer.Bind();
    m_SpriteShader.Bind();

    if (const auto& sprite = m_Sprite.lock())
    {
        sprite->BindTexture();
        m_SpriteShader.SetUniformI("uTexture", 0);
        
        auto scaleMatrix = glm::mat4(1.0f);
        scaleMatrix = scale(scaleMatrix, glm::vec3( sprite->GetWidthF(),sprite->GetHeightF(), 1.f));

        const auto actorWorldTransform = m_OwnerActor->GetTransform().GetWorldTransform();
        const auto worldMatrix = actorWorldTransform * scaleMatrix;
        
        m_SpriteShader.SetUniformM4("uWorldTransform", worldMatrix);
    }
    else
    {
        m_SpriteShader.SetUniformM4("uWorldTransform", m_OwnerActor->GetTransform().GetWorldTransform());
    }
    
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr))
}

void SpriteRenderer::SetSprite(const std::weak_ptr<Sprite>& newSprite)
{
    m_Sprite = newSprite;
}

void SpriteRenderer::SetDrawOrder(int drawOrder)
{
    m_DrawOrder = drawOrder;
}

int SpriteRenderer::GetTexHeight() const
{
    if (const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
    return 0;
}

int SpriteRenderer::GetTextWidth() const
{
    if (const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
    return 0;
}

float SpriteRenderer::GetRotationDegrees() const
{
    return glm::degrees(m_OwnerActor->GetTransform().GetRotation());
}