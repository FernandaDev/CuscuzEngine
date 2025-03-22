#pragma once

#include <string>
#include "glm.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

namespace Cuscuz
{
    namespace Editor
    {
        enum
        {
            Font_Regular = 0,
            Font_Bold = 1,
        };
        
        inline static void DrawVec3Control(const std::string& label, glm::vec3& values, float columnWidth = 100.0f)
        {
            ImGuiIO& io = ImGui::GetIO();
            const auto boldFont = io.Fonts->Fonts[Font_Bold];
            
            ImGui::PushID(label.c_str());
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, columnWidth);
            
            ImGui::Text(label.c_str());

            ImGui::NextColumn();

            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

            ImGui::PushFont(boldFont);
            ImGui::AlignTextToFramePadding();
            ImGui::Text("X");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##x", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Y");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Z");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            
            ImGui::Columns(1);

            ImGui::PopID();
        }
    }
}
