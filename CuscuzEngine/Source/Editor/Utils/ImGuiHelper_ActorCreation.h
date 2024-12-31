#pragma once

#include "imgui.h"
#include "World/World.h"

namespace ImGuiHelper
{
    inline static void ShowActorCreation(bool& showing, World* world)
    {
        ImGui::Begin("New Actor", &showing);

        ImGui::Text("Name");
        ImGui::Separator();

        static char newActorName[128] = "";
        ImGui::InputText("##Name", newActorName, IM_ARRAYSIZE(newActorName));

        ImGui::Dummy(ImVec2(0.0f, 3.0f));

        ImGui::Text("Position");
        ImGui::Separator();
        
        static ImVec4 pos(0,0,0,0);
        ImGui::DragFloat("x##pos", &pos.x);
        ImGui::DragFloat("y##pos", &pos.y);
        ImGui::DragFloat("z##pos", &pos.z);
        
        if (ImGui::Button("Create"))
        {
            world->CreateActor(newActorName, {pos.x, pos.y, pos.z});
            showing = false;
        }
        
        ImGui::End();
    }
}
