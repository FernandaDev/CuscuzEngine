#pragma once

#include "Cuscuz.h"
#include "ImGui/imgui.h"

namespace Cuscuz::Editor
{
    inline static void ShowActorCreation(World* world)
    {
        ImGui::Text("Name");
        ImGui::Separator();

        static char newActorName[128] = "";
        ImGui::InputText("##Name", newActorName, IM_ARRAYSIZE(newActorName));

        ImGui::Dummy(ImVec2(0.0f, 3.0f));

        ImGui::Text("Position");
        ImGui::Separator();

        static ImVec4 pos(0, 0, 0, 0);
        ImGui::DragFloat("x##pos", &pos.x);
        ImGui::DragFloat("y##pos", &pos.y);
        ImGui::DragFloat("z##pos", &pos.z);

        if (ImGui::Button("Create"))
        {
        }
    }
}
