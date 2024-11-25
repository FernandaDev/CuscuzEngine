#pragma once

#include "ImGui/imgui.h"
#include "World/World.h"
#include "World/Actor.h"

namespace ImGuiHelper
{
    static bool showingActor = false;

    inline static void ShowActorTransform(Actor* actor)
    {
        ImGui::Text("Transform");

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 3.0f));

        ImGui::PushItemWidth(100.0f); 
        
        ImGui::Text("Position");
        auto actorPos = actor->GetTransform().GetPosition();
        
        ImGui::DragFloat("x##pos", &actorPos.x);
        ImGui::DragFloat("y##pos", &actorPos.y);

        actor->GetTransform().SetPosition(actorPos);

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        
        ImGui::Text("Rotation");

        auto actorRot = actor->GetTransform().GetRotation();

        ImGui::DragFloat("degrees", &actorRot);

        actor->GetTransform().SetRotation(actorRot);
        
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        
        ImGui::Text("Scale");
        
        auto actorScale =  actor->GetTransform().GetScale();

        ImGui::DragFloat("x##scale", &actorScale.x);
        ImGui::DragFloat("y##scale", &actorScale.y);
        
        actor->GetTransform().SetScale(actorScale);

        ImGui::PopItemWidth();
        ImGui::Dummy(ImVec2(0.0f, 3.0f));
        ImGui::Separator();
    }
    
    inline static void ShowActor(Actor* actor, int index)
    {
        ImGui::PushID(index);

        ImGui::Begin(actor->GetName().c_str(), &showingActor);

        if (ImGui::BeginTabBar("##TabBar"))
        {
            if (ImGui::BeginTabItem("Transform"))
            {
                ShowActorTransform(actor);
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Components"))
            {
                ImGui::Text("TO DO");
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        
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
