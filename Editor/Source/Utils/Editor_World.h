#pragma once

#include "ImGui/imgui.h"
#include "Editor_Components.h"
#include "Cuscuz/World/World.h"
#include "Cuscuz/World/Actor.h"
#include "Cuscuz/World/Level.h"

namespace Cuscuz::Editor
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

        ShowActorComponents(actor);
    }

    static Actor* s_SelectedActor = nullptr;

    inline static void ShowAllActors(World* world)
    {
        const auto allActors = world->GetActiveLevel()->GetAllActors();

        for (auto& actor : allActors)
        {
            ImGuiTreeNodeFlags flags = ((actor.get() == s_SelectedActor) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
            const bool isOpened = ImGui::TreeNodeEx(actor.get(), flags, actor->GetName().c_str());

            if (ImGui::IsItemClicked())
                s_SelectedActor = actor.get();

            bool actorDeleted = false;
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Actor"))
                    actorDeleted = true;

                ImGui::EndPopup();
            }

            if (isOpened)
            {
                //TODO show child!
                ImGui::TreePop();
            }

            if (actorDeleted)
            {
                if (s_SelectedActor == actor.get())
                    s_SelectedActor = {};
                world->DestroyActor(actor);
            }
        }
    }
}
