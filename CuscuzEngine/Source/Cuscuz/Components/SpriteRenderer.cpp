﻿#include "pch.h"

#include "imgui.h"
#include "SpriteRenderer.h"
#include "gtc/matrix_transform.hpp"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/World/Actor.h"
//#include "Cuscuz/Editor/Utils/ImGuiHelper_Resources.h"
#include "gtc/type_ptr.inl"
#include "Cuscuz/Render/Renderer2D.h"
#include "Cuscuz/World/Scene.h"
#include "Proxys/SpriteRendererProxy.h"

namespace Cuscuz
{
    CREATE_COMPONENT_REGISTRY(SpriteRenderer);

    SpriteRenderer::SpriteRenderer(int drawOrder) :
    m_DrawOrder(drawOrder), m_Color(1.f, 1.f, 1.f, 1)
    { }

    void SpriteRenderer::OnAdded()
    {
        Scene::GetOnDrawableProxyAddedEvent().Broadcast(this); //TODO create and pass the proxy
    }

    void SpriteRenderer::OnRemoved()
    {
        Scene::GetOnDrawableProxyRemovedEvent().Broadcast(this);
    }

    void SpriteRenderer::Draw()
    {
        if(!m_Sprite)
            return;

        const auto transform = m_OwnerActor->GetTransform().GetWorldTransform();

        if(const auto texture = m_Sprite->GetTexture())
            Renderer2D::DrawQuad(transform, m_Color, texture);
        else
            Renderer2D::DrawQuad(transform, m_Color);
    }

    void SpriteRenderer::SetSprite(const CC_AssetRef<Sprite>& newSprite)
    {
        m_Sprite = newSprite;
    }

    void SpriteRenderer::SetDrawOrder(uint32_t drawOrder)
    {
        m_DrawOrder = drawOrder;
    }

    void SpriteRenderer::SetColor(glm::vec4 color)
    {
        m_Color = color;
    }

    uint32_t SpriteRenderer::GetTexHeight() const
    {
        if (m_Sprite)
            return m_Sprite->GetHeight();

        LOG_WARN("You are trying to get a sprite's Height, but there is no sprite!");
        return 0;
    }

    uint32_t SpriteRenderer::GetTextWidth() const
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

    // void SpriteRenderer::ImGuiDisplayComponent()
    // {
    //     ImGui::Text("Color");
    //     ImGui::SameLine();
    //
    //     static glm::vec4 spriteColor = m_Color;
    //     ImGui::ColorEdit4("#SpriteColor", glm::value_ptr(spriteColor));
    //
    //     if(spriteColor != m_Color)
    //         SetColor(spriteColor);
    //
    //     ImGui::NewLine();
    //
    //     ImGui::Text("Sprite");
    //     ImGui::SameLine();
    //
    //     const ImVec2 initialPoint = ImGui::GetCursorScreenPos();
    //     constexpr ImVec4 color(.5f,.8f,1.f,1.f);
    //         
    //     ImDrawList* draw_list = ImGui::GetWindowDrawList();
    //
    //     if(m_Sprite)
    //     {
    //         if(const auto texture = m_Sprite->GetTexture())
    //         {
    //             const auto width = m_Sprite->GetWidthF();
    //             const auto height = m_Sprite->GetHeightF();
    //             constexpr float offset = 1.f;
    //             
    //             draw_list->AddRect(ImVec2(initialPoint.x - offset,initialPoint.y -offset),
    //                 ImVec2(initialPoint.x + width + offset, initialPoint.y + height + offset),
    //                 ImColor(color));
    //
    //             ImGui::Image((void*)(intptr_t)texture->GetRendererID(),
    //                 {m_Sprite->GetWidthF(), m_Sprite->GetHeightF()});
    //
    //             ImGui::TextColored(ImVec4(0.6f, .6f, .6f, .8f), "Width:%f | Height:%f", width, height);
    //         }
    //     }
    //     else
    //     {
    //         constexpr float squareSize = 64.f;
    //         const float x = initialPoint.x + 4.0f;
    //         const float y = initialPoint.y + 4.0f;
    //         
    //         draw_list->AddRect(ImVec2(x,y), ImVec2(x + squareSize,y + squareSize), ImColor(color));
    //
    //         ImGui::NewLine();
    //
    //         static bool showingAllTextures = false;
    //         
    //         if(ImGui::Button("Add##Sprite"))
    //         {
    //             LOG_INFO("Trying to add a sprite");
    //             showingAllTextures = true;
    //         }
    //
    //         if(showingAllTextures)
    //             ImGuiHelper::ShowAllTextureResources(showingAllTextures, this);
    //         
    //         ImGui::Dummy(ImVec2(0.0f, squareSize));
    //     }
    // }
}
