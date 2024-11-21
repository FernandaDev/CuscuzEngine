#pragma once

#include "ImGui/imgui.h"
#include "World/World.h"

namespace ImGuiHelper
{
    inline static void ShowActorCreation(bool showing, World* world)
    {
        if (!showing)
            return;

        ImGui::BeginGroup();

        // Grab the name
        static char newActorName[128] = "";
        ImGui::InputText("Name", newActorName, IM_ARRAYSIZE(newActorName));

        // Grab the initial position
        static ImVec2 pos(0,0);
        ImGui::InputFloat2("Position", &pos.x);

        if (ImGui::Button("Create Actor"))
            world->CreateActor(newActorName, {pos.x, pos.y});

        ImGui::EndGroup();
    }
}
