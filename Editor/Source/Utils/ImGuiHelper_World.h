#pragma once

#include "ImGui/imgui.h"
#include "ImGuiHelper_ActorComponents.h"
#include "Cuscuz/World/World.h"
#include "Cuscuz/World/Actor.h"

namespace ImGuiHelper
{
    inline static void ShowActor(Cuscuz::Actor* actor)
    {
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.f), actor->GetName().c_str());

        ImGui::Separator();
        
        actor->GetTransform().ImGuiDisplayComponent();
    }
    
    static Cuscuz::Actor* selectedActor = nullptr;
    static uint32_t selectedIndex = 0;

    inline static void ShowAllActors(Cuscuz::World* world)
    {
        const auto allActors = world->GetAllActors();

        for (size_t actorIndex = 0; actorIndex < allActors.size(); actorIndex++)
        {
            if (const auto actor = allActors[actorIndex].get())
            {
                ImGui::PushID(static_cast<uint32_t>(actorIndex));

                if (ImGui::Button(actor->GetName().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {
                    selectedActor = actor;
                    selectedIndex = static_cast<uint32_t>(actorIndex);
                }

                ImGui::PopID();
            }
        }
        //
        // if (selectedActor && showingActor)
        //     ShowActor(selectedActor, selectedIndex);
    }
}
