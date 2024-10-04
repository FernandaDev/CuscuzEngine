#pragma once

#include "ImGui/imgui.h"
#include "World/World.h"
#include "World/Actor.h"

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

inline static void ShowAddComponentBar(Actor* actor, int index)
{
    const char* items[] = { "Option 1", "Option 2", "Option 3" };
    static int currentItem = 0;  // Index of the currently selected item

    // Create the combo box (dropdown)
    if (ImGui::Combo("Add Component", &currentItem, items, IM_ARRAYSIZE(items)))
    {
        //TODO
    }
}

inline static void ShowActorComponents(Actor* actor, int index)
{
    ImGui::TextColored(ImVec4(0.f,.5f,1.f,1.f),"Components");
    
    const auto listLabel = "##" + std::to_string(index);
    ImGui::BeginListBox(listLabel.c_str(), ImVec2(300, 50));
    
    for (const auto& component : actor->GetComponents())
        ImGui::Text(component->GetComponentType().data());

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
    ImGui::Text("X: %f ", actor->GetPosition().x);
    ImGui::SameLine();
    ImGui::Text("Y: %f ", actor->GetPosition().y);
    
    ImGui::Text("Rotation: %f", actor->GetRotation());
    ImGui::Text("Scale: %f", actor->GetScale());
    
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
