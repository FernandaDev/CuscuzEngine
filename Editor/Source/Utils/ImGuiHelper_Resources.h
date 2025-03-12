#pragma once
#include "ImGui/imgui.h"
#include "Cuscuz/Components/SpriteRenderer.h"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/Render/Texture.h"
#include "Cuscuz/Utils/ResourcesManager.h"

namespace ImGuiHelper
{
    inline static void ShowAllTextureResources(bool& showingAllTextures, Cuscuz::SpriteRenderer* spriteRenderer)
    {
        // ImGui::Begin("Textures", &showingAllTextures);
        //
        // const std::vector<std::reference_wrapper<Texture>> textures = ResourcesManager::Get().GetAllTextures();
        //
        // for (const auto& texture : textures)
        // {
        //     if (ImGui::ImageButton((void*)(intptr_t)texture.get().GetRendererId(), ImVec2(64, 64)))
        //     {
        //         LOG_INFO("Selected Texture Name: %s", texture.get().GetName().c_str());
        //         const auto sprite = std::make_shared<Sprite>();
        //         sprite->SetTexture(&texture.get());
        //         spriteRenderer->SetSprite(sprite);
        //         showingAllTextures = false;
        //     }
        //
        //     ImGui::SameLine();
        // }
        //
        // ImGui::End();
    }
}
