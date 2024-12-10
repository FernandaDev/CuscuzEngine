#include "pch.h"
#include "SpriteRenderer.h"

#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "Render/Sprite.h"
#include "World/Actor.h"
#include "Render/VertexArray.h"
#include "Render/VertexBufferLayout.h"
#include "imgui.h" //TODO remember to disable on dist
#include "Editor/Utils/ImGuiHelper_Resources.h"
#include "Render/Renderer.h"

CREATE_COMPONENT_REGISTRY(SpriteRenderer);

SpriteRenderer::SpriteRenderer(int drawOrder) :
    m_DrawOrder(drawOrder), m_Color(0, 0, 0, 1)
{
    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::Create(m_Vertices,  4 * 5 * sizeof(float)));
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(m_Indices, 6));

    const BufferLayout layout =
    {
        { ShaderDataType::Float3, "inPosition" },
        { ShaderDataType::Float2, "inTexCoord" }
    };
    
    vertexBuffer->SetLayout(layout);
    
    m_VertexArray.reset(VertexArray::Create());
    m_VertexArray->AddBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
    
    LoadShaders();
}

bool SpriteRenderer::LoadShaders()
{
    if (!m_Shader.Load("Assets/Shaders/Sprite.glsl"))
        return false;

    m_Shader.Bind();

    const auto viewProj = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH),
                                                     0.0f,static_cast<float>(SCREEN_HEIGHT),
                                               -1.0f, 1.0f);
    m_Shader.SetUniformM4("uViewProjection", viewProj);

    return true;
}

void SpriteRenderer::Draw()
{
    m_Shader.Bind();

    if (m_Sprite)
    {
        m_Sprite->BindTexture();
        m_Shader.SetUniformI("uTexture", 0);
        
        auto scaleMatrix = glm::mat4(1.0f);
        scaleMatrix = scale(scaleMatrix, glm::vec3( m_Sprite->GetWidthF(),m_Sprite->GetHeightF(), 1.f));

        const auto actorWorldTransform = m_OwnerActor->GetTransform().GetWorldTransform();
        const auto worldMatrix = actorWorldTransform * scaleMatrix;
        
        m_Shader.SetUniformM4("uWorldTransform", worldMatrix);
    }
    else
    {
        m_Shader.SetUniformM4("uWorldTransform", m_OwnerActor->GetTransform().GetWorldTransform());
    }

    Renderer::Submit(m_VertexArray);
}

void SpriteRenderer::SetSprite(Sprite* newSprite)
{
    m_Sprite = newSprite;
}

void SpriteRenderer::SetDrawOrder(int drawOrder)
{
    m_DrawOrder = drawOrder;
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

            ImGui::Image((void*)(intptr_t)texture->GetRendererId(),
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
