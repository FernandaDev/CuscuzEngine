#pragma once

#include <ranges>
#include <vector>

#include "ImGui/imgui.h"
#include "World/Actor.h"
#include "Core/ClassRegistry.h"

namespace ImGuiHelper
{
    inline static bool ItemGetter(void* data, int idx, const char** out_text)
    {
        const std::vector<std::string>* items = static_cast<std::vector<std::string>*>(data);
        if (idx < 0 || idx >= items->size()) return false; // Out of bounds check
        *out_text = (*items)[idx].c_str();
        return true;
    }

    inline static void ShowAddComponentBar(Actor* actor, int index)
    {
        const auto registry = ClassRegistry::GetRegistry();

        std::vector<std::string> items;
        items.reserve(registry.size());

        for (const auto& registryKey : registry | std::views::keys)
        {
            items.emplace_back(registryKey);
        }

        static int currentItem = 0; // Index of the currently selected item

        const auto componentsListLabel = "Components List##" + std::to_string(index);

        if (ImGui::Combo(componentsListLabel.c_str(), &currentItem, ItemGetter, &items, static_cast<int>(items.size())))
        {
            LOG_INFO("Selected component: {0}", items[currentItem]);
        }

        const auto addLabel = "Add##" + std::to_string(index);

        if (ImGui::Button(addLabel.c_str()))
        {
            auto selectedComponent = ClassRegistry::GetClassType(items[currentItem]);

            if (!selectedComponent)
                return;

            const auto newComponent = Instantiate<Component>(selectedComponent->Name);
            actor->AddComponent(newComponent);
        }
    }

    inline static void ShowActorComponents(Actor* actor, int index)
    {
        ImGui::TextColored(ImVec4(0.f, .5f, 1.f, 1.f), "Components");

        const auto listLabel = "##" + std::to_string(index);
        ImGui::BeginListBox(listLabel.c_str(), ImVec2(300, 50));

        for (const auto& component : actor->GetComponents())
        {
            ImGui::Text(component->GetComponentType().c_str());
        }

        ImGui::EndListBox();
    }
    
}