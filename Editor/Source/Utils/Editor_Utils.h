#pragma once

#include <string>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

namespace Cuscuz::Editor
{
    enum
    {
        Font_Regular = 0,
        Font_Bold = 1,
    };

    inline static void DrawIntControl(const std::string& label, uint32_t& value, float columnWidth = 100.0f)
    {
        ImGui::PushID(label.c_str());
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);

        ImGui::Text(label.c_str());

        ImGui::NextColumn();

        ImGui::PushItemWidth(ImGui::CalcItemWidth());

        int tempValue = static_cast<int>(value);
        ImGui::DragInt("##x", &tempValue);
        value = std::max(tempValue, 0);

        ImGui::PopItemWidth();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    inline static void DrawIntControl(const std::string& label, int& value, float columnWidth = 100.0f)
    {
        ImGui::PushID(label.c_str());
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);

        ImGui::Text(label.c_str());

        ImGui::NextColumn();

        ImGui::PushItemWidth(ImGui::CalcItemWidth());

        ImGui::DragInt("##x", &value);

        ImGui::PopItemWidth();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    inline static void DrawFloatControl(const std::string& label, float& value, float columnWidth = 100.0f)
    {
        ImGui::PushID(label.c_str());
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);

        ImGui::Text(label.c_str());

        ImGui::NextColumn();

        ImGui::PushItemWidth(ImGui::CalcItemWidth());

        ImGui::DragFloat("##x", &value, 0.1f, 0.0f, 0.0f, "%.2f");

        ImGui::PopItemWidth();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    inline static void DrawVec2Control(const std::string& label, glm::vec2& values, float columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        const auto boldFont = io.Fonts->Fonts[Font_Bold];

        ImGui::PushID(label.c_str());
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);

        ImGui::Text(label.c_str());

        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

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

        ImGui::Columns(1);

        ImGui::PopID();
    }

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
