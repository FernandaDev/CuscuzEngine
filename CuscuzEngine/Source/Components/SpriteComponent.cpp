#include "pch.h"
#include "SpriteComponent.h"

#include "detail/func_trigonometric.inl"
#include "Render/Sprite.h"
#include "World/Actor.h"
#include "GL/glew.h"

CREATE_COMPONENT_REGISTRY(SpriteComponent);

SpriteComponent::SpriteComponent(int drawOrder) :
m_DrawOrder(drawOrder), m_Color(0,0,0,1)
{
    m_SpriteVerts = std::make_unique<VertexArray>(vertexPositions, 4, indexBuffer, 6);
    LoadShaders();
}

void SpriteComponent::Draw()
{
    m_SpriteShader->SetActive();
    m_SpriteVerts->SetActive();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetSprite(std::weak_ptr<Sprite> newSprite)
{
    m_Sprite = std::move(newSprite);
}

void SpriteComponent::SetDrawOrder(int drawOrder)
{
    m_DrawOrder = drawOrder;
}

int SpriteComponent::GetTexHeight() const
{
    if(const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
    return 0;
}

int SpriteComponent::GetTextWidth() const
{
    if(const auto SharedSprite = m_Sprite.lock())
        return SharedSprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
    return 0;
}

float SpriteComponent::GetRotationDegrees() const
{
    return glm::degrees(m_OwnerActor->GetRotation());
}

bool SpriteComponent::LoadShaders()
{
    m_SpriteShader = std::make_unique<Shader>();

    if(!m_SpriteShader->Load("Assets/Shaders/Basic.glsl"))
        return false;

    m_SpriteShader->SetActive();
    return true;
}