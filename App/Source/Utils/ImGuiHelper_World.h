#pragma once

#include <ranges>

#include "Components/Animation2DComponent.h"
#include "ImGui/imgui.h"
#include "World/World.h"
#include "World/Actor.h"
#include "Core/ClassRegistry.h"
#include "Components/Simple2DMovementComponent.h"

inline static void ShowActorCreation(bool showing, World* world)
{
    if(!showing)
        return;
    
    ImGui::BeginGroup();

    // Grab the name
    static char newActorName[128] = "";
    ImGui::InputText("Name", newActorName, IM_ARRAYSIZE(newActorName));

    // Grab the initial position
    static glm::i32vec2 pos(0,0);
    ImGui::InputInt2("Position", &pos.x);

    if(ImGui::Button("Create Actor"))
        world->CreateActor(newActorName, pos);
    
    ImGui::EndGroup();
}

inline static bool ItemGetter(void* data, int idx, const char** out_text)
{
    const std::vector<std::string>* items = static_cast<std::vector<std::string>*>(data);
    if (idx < 0 || idx >= items->size()) return false;  // Out of bounds check
    *out_text = (*items)[idx].c_str();
    return true;
}

inline static void ShowAddComponentBar(Actor* actor, int index)
{
    const auto registry = ClassRegistry::GetRegistry();

    std::vector<std::string> items;
    items.reserve(registry.size());

    for(const auto& registryKey : registry | std::views::keys)
    {
        items.emplace_back(registryKey);
    }
    
    static int currentItem = 0;  // Index of the currently selected item

    const auto componentsListLabel = "Components List##" + std::to_string(index);
    
    if(ImGui::Combo(componentsListLabel.c_str(), &currentItem, ItemGetter, &items, static_cast<int>(items.size())))
    {
        LOG_INFO("Selected component: {0}", items[currentItem]);
    }

    const auto addLabel = "Add##" + std::to_string(index);
    
    if(ImGui::Button(addLabel.c_str()))
    {
        auto selectedComponent = ClassRegistry::GetClassType(items[currentItem]);

        if(!selectedComponent)
            return;
        
        const auto newComponent = Instantiate<Component>(selectedComponent->Name);
        actor->AddComponent(newComponent);
    }
}


inline static void ShowActorComponents(Actor* actor, int index)
{
    ImGui::TextColored(ImVec4(0.f,.5f,1.f,1.f),"Components");
    
    const auto listLabel = "##" + std::to_string(index);
    ImGui::BeginListBox(listLabel.c_str(), ImVec2(300, 50));
    
    for (const auto& component : actor->GetComponents())
    {
        ImGui::Text(component->GetComponentType().c_str());
    }

    ImGui::EndListBox();
}

inline static void ShowActor(Actor* actor, int index, World* world)
{
    ImGui::BeginGroup();
            
    ImGui::Text(actor->GetName().c_str());
    ImGui::SameLine();

    const auto destroyLabel = "Destroy##" + std::to_string(index);
    if(ImGui::Button(destroyLabel.c_str()))
        world->DestroyActor(actor);
    
    ImGui::Text("Position: ");
    ImGui::SameLine();
    ImGui::Text("X: %f ", actor->GetTransform().GetPosition().x);
    ImGui::SameLine();
    ImGui::Text("Y: %f ", actor->GetTransform().GetPosition().y);
    
    ImGui::Text("Rotation: %f", actor->GetTransform().GetRotation());
    ImGui::Text("Scale: %f", actor->GetTransform().GetScale());
    
    ImGui::Spacing();
    ShowActorComponents(actor, index);
    ImGui::Spacing();
    ShowAddComponentBar(actor, index);
    ImGui::Spacing();
    
    ImGui::EndGroup();
    ImGui::Separator();
}

inline static void ShowAllActors(bool showing, World* world)
{
    if(!showing)
        return;
    
    const auto allActors = world->GetAllActors();
    
    for (size_t i = 0; i < allActors.size(); ++i)
    {
        if(const auto actor = allActors[i].get())
            ShowActor(actor, static_cast<int>(i), world);
    }
}
