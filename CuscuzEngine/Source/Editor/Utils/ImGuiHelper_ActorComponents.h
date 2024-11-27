#pragma once

#include <ranges>
#include <vector>

#include "imgui.h"
#include "ImGuiHelper_SpriteRenderer.h"
#include "Components/SpriteRenderer.h"
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

        ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Components List");
        
        const auto componentsListLabel = "##ComponentList" + std::to_string(index);

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

    inline static void ShowComponent(Component* component)
    {
        if(const auto spriteRenderer = dynamic_cast<SpriteRenderer*>(component))
        {
            ShowSpriteRenderer(spriteRenderer);
        }
        //else if...
    }
    
    inline static void ShowActorComponents(Actor* actor, int index)
    {
        ShowAddComponentBar(actor, index);
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        
        ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Components");

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 3.0f));
        
        for (const auto& component : actor->GetComponents())
        {
            if(ImGui::CollapsingHeader(component->GetComponentType().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
                ShowComponent(component.get());

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
            ImGui::Separator();
        }
    }
    
}
