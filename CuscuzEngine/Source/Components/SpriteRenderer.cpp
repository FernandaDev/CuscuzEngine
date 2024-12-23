#include "pch.h"
#include "SpriteRenderer.h"
#include "ext/matrix_transform.hpp"
#include "Render/Sprite.h"
#include "World/Actor.h"
#include "Render/VertexArray.h"
#include "Editor/Utils/ImGuiHelper_Resources.h"
#include "gtc/type_ptr.inl"
#include "Render/Renderer.h"

CREATE_COMPONENT_REGISTRY(SpriteRenderer);

SpriteRenderer::SpriteRenderer(int drawOrder) :
     m_DrawOrder(drawOrder), m_Color(1.f, 1.f, 1.f, 1)
{
    const CC_AssetRef<VertexBuffer> vertexBuffer = VertexBuffer::Create(m_Vertices,  4 * 5 * sizeof(float));
    const CC_AssetRef<IndexBuffer> indexBuffer = IndexBuffer::Create(m_Indices, 6);

    const BufferLayout layout =
    {
        { ShaderDataType::Float3, "inPosition" },
        { ShaderDataType::Float2, "inTexCoord" }
    };
    
    vertexBuffer->SetLayout(layout);
    
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_Shader = m_ShaderLib.Get("Sprite");
    
    SetColor(m_Color);
}

void SpriteRenderer::Draw()
{
    m_Shader->Bind();

     if (m_Sprite)
     {
         m_Sprite->BindTexture();
         m_Shader->SetUniformI("u_Texture", 0);
         
         auto scaleMatrix = glm::mat4(1.0f);
         scaleMatrix = scale(scaleMatrix, glm::vec3( m_Sprite->GetWidthF(),m_Sprite->GetHeightF(), 1.f));
    
         const auto actorWorldTransform = m_OwnerActor->GetTransform().GetWorldTransform();
         const auto worldMatrix = actorWorldTransform * scaleMatrix;
         
         m_Shader->SetUniformM4("u_WorldTransform", worldMatrix);
     }
     else
    {
        m_Shader->SetUniformM4("u_WorldTransform", m_OwnerActor->GetTransform().GetWorldTransform());
    }

    Renderer::Submit(m_Shader, m_VertexArray);
}

void SpriteRenderer::SetSprite(const CC_AssetRef<Sprite>& newSprite)
{
    m_Sprite = newSprite;
}

void SpriteRenderer::SetDrawOrder(int drawOrder)
{
    m_DrawOrder = drawOrder;
}

void SpriteRenderer::SetColor(glm::vec4 color)
{
    m_Color = color;
    m_Shader->Bind();
    m_Shader->SetUniformF4("u_Color", color);
}

int SpriteRenderer::GetTexHeight() const
{
    if (m_Sprite)
        return m_Sprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
    return 0;
}

int SpriteRenderer::GetTextWidth() const
{
    if (m_Sprite)
        return m_Sprite->GetHeight();

    LOG_WARN("You are trying to get a sprite's Width, but there is no sprite!");
    return 0;
}

float SpriteRenderer::GetRotationDegrees() const
{
    return glm::degrees(m_OwnerActor->GetTransform().GetRotation());
}

void SpriteRenderer::ImGuiDisplayComponent()
{
    ImGui::Text("Color");
    ImGui::SameLine();
    
    static glm::vec4 spriteColor (1.f);
    ImGui::ColorEdit4("#SpriteColor", glm::value_ptr(spriteColor));

    if(spriteColor != m_Color)
        SetColor(spriteColor);
    
    ImGui::NewLine();

    ImGui::Text("Sprite");
    ImGui::SameLine();

    const ImVec2 initialPoint = ImGui::GetCursorScreenPos();
    constexpr ImVec4 color(.5f,.8f,1.f,1.f);
            
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if(m_Sprite)
    {
        if(const auto texture = m_Sprite->GetTexture())
        {
            const auto width = m_Sprite->GetWidthF();
            const auto height = m_Sprite->GetHeightF();
            constexpr float offset = 1.f;
                
            draw_list->AddRect(ImVec2(initialPoint.x - offset,initialPoint.y -offset),
                ImVec2(initialPoint.x + width + offset, initialPoint.y + height + offset),
                ImColor(color));

            ImGui::Image((void*)(intptr_t)texture->GetRendererID(),
                {m_Sprite->GetWidthF(), m_Sprite->GetHeightF()});

            ImGui::TextColored(ImVec4(0.6f, .6f, .6f, .8f), "Width:%f | Height:%f", width, height);
        }
    }
    else
    {
        constexpr float squareSize = 64.f;
        const float x = initialPoint.x + 4.0f;
        const float y = initialPoint.y + 4.0f;
            
        draw_list->AddRect(ImVec2(x,y), ImVec2(x + squareSize,y + squareSize), ImColor(color));

        ImGui::NewLine();

        static bool showingAllTextures = false;
            
        if(ImGui::Button("Add##Sprite"))
        {
            LOG_INFO("Trying to add a sprite");
            showingAllTextures = true;
        }

        if(showingAllTextures)
            ImGuiHelper::ShowAllTextureResources(showingAllTextures, this);
            
        ImGui::Dummy(ImVec2(0.0f, squareSize));
    }
}
