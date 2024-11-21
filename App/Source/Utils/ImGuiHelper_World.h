#pragma once

#include "ImGui/imgui.h"
#include "World/World.h"
#include "World/Actor.h"

namespace ImGuiHelper
{
    static bool showingActor = false;
    
    inline static void ShowActor(Actor* actor, int index)
    {
        ImGui::PushID(index);
        //const auto name = actor->GetName() + std::to_string(index);
        ImGui::Begin(actor->GetName().c_str(), &showingActor);
        
        ImGui::Text(actor->GetName().c_str());
        
        ImGui::Separator();
        
        ImGui::BeginListBox("Transform");
        
        ImGui::Text("Position: (%.1f, %.1f)", actor->GetTransform().GetPosition().x,
                                                 actor->GetTransform().GetPosition().y);
        
        ImGui::Text("Rotation: %f", actor->GetTransform().GetRotation());
        ImGui::Text("Scale: %f", actor->GetTransform().GetScale());
        
        ImGui::EndListBox();
        
        ImGui::End();
        
        ImGui::PopID();
    }
    
     inline static void ShowAllActors(bool showing, World* world)
     {
         if (!showing)
             return;
    
         static Actor* selectedActor = nullptr;
         static int selectedIndex = 0;
    
         const auto allActors = world->GetAllActors();
    
         for (int actorIndex = 0; actorIndex < allActors.size(); actorIndex++)
         {
             if (const auto actor = allActors[actorIndex].get())
             {
                 ImGui::PushID(actorIndex);
                 //const auto actorName = actor->GetName()+ "##" + std::to_string(actorIndex);
                 if(ImGui::Button(actor->GetName().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                 {
                     selectedActor = actor;
                     selectedIndex = actorIndex;
                     showingActor = true;
                 }
                 ImGui::PopID();
             }
         }
    
         if(selectedActor && showingActor)
             ShowActor(selectedActor, selectedIndex);
    }
}
