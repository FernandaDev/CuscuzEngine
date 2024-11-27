#pragma once
#include "imgui.h"
#include "Components/SpriteRenderer.h"
#include "Render/Sprite.h"
#include "Render/Texture.h"
#include "Utils/ResourcesManager.h"

namespace ImGuiHelper
{
    inline static void ShowAllTexture(bool& showingAllTextures, SpriteRenderer* spriteRenderer)
    {
        ImGui::Begin("Textures", &showingAllTextures);

        std::vector<std::reference_wrapper<Texture>> textures = ResourcesManager::Get().GetAllTextures();

        for (Texture& texture : textures)
        {
            if (ImGui::ImageButton((void*)(intptr_t)texture.GetRendererId(), ImVec2(64, 64)))
            {
                LOG_INFO("Selected Texture Name: %s", texture.GetName().c_str());
                const auto sprite = new Sprite();
                sprite->SetTexture(&texture);
                spriteRenderer->SetSprite(sprite);
                showingAllTextures = false;
            }

            ImGui::SameLine();
        }
        
        ImGui::End();
    }
    
    inline static void ShowSpriteRenderer(SpriteRenderer* spriteRenderer)
    {
        ImGui::Text("Sprite");
        ImGui::SameLine();

        const ImVec2 initialPoint = ImGui::GetCursorScreenPos();
        constexpr ImVec4 color(.5f,.8f,1.f,1.f);
            
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if(const auto sprite = spriteRenderer->GetSprite())
        {
            if(const auto texture = sprite->GetTexture())
            {
                const auto width = sprite->GetWidthF();
                const auto height = sprite->GetHeightF();
                constexpr float offset = 1.f;
                
                draw_list->AddRect(ImVec2(initialPoint.x - offset,initialPoint.y -offset),
                    ImVec2(initialPoint.x + width + offset, initialPoint.y + height + offset),
                    ImColor(color));

                ImGui::Image((void*)(intptr_t)texture->GetRendererId(),
                    {sprite->GetWidthF(), sprite->GetHeightF()});

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
                ShowAllTexture(showingAllTextures, spriteRenderer);
            
            ImGui::Dummy(ImVec2(0.0f, squareSize));
        }
    }
}
