#pragma once

#include "ImGui/imgui.h"
#include "Editor_ActorComponents.h"
#include "Cuscuz/World/World.h"
#include "Cuscuz/World/Actor.h"

namespace Cuscuz
{
    namespace Editor
    {
        inline static void ShowActor(Actor* actor)
        {
            const std::string actorName = actor->GetName();

            char nameBuffer[256];
            strncpy_s(nameBuffer, actorName.c_str(), sizeof(nameBuffer));
            nameBuffer[sizeof(nameBuffer) - 1] = '\0';

            if (ImGui::InputText("##ActorName", nameBuffer, sizeof(nameBuffer)))
                actor->SetName(nameBuffer);

            ImGui::Dummy({0, 5});

            actor->GetTransform().ImGuiDisplayComponent();
        }

        static Actor* s_SelectedActor = nullptr;

        inline static void ShowAllActors(World* world)
        {
            const auto allActors = world->GetAllActors();

            for(auto& actor : allActors)
            {
                ImGuiTreeNodeFlags flags = ( (actor.get() == s_SelectedActor) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
                const bool isOpened = ImGui::TreeNodeEx(actor.get(), flags, actor->GetName().c_str());

                if(ImGui::IsItemClicked())
                    s_SelectedActor = actor.get();

                if(isOpened)
                {
                    //TODO show child!
                    ImGui::TreePop();
                }
            }
        }
    }
}
