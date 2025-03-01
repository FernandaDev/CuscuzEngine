#pragma once

#include "imgui.h"
#include "ImGuiHelper_ActorComponents.h"
#include "Cuscuz/Core/RendererSystem.h"
#include "Cuscuz/World/World.h"
#include "Cuscuz/World/Actor.h"

namespace ImGuiHelper
{
    static bool showingActor = false;
    
    inline static void ShowActor(Cuscuz::Actor* actor, int index)
    {
        ImGui::PushID(index);

        ImGui::Begin(actor->GetName().c_str(), &showingActor);

        if (ImGui::BeginTabBar("##TabBar"))
        {
            if (ImGui::BeginTabItem("Transform"))
            {
                actor->GetTransform().ImGuiDisplayComponent();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Components"))
            {
                ShowActorComponents(actor, index);
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        
        ImGui::End();
        ImGui::PopID();
    }
    
     inline static void ShowAllActors(bool showing, Cuscuz::World* world)
     {
         if (!showing)
             return;
    
         static Cuscuz::Actor* selectedActor = nullptr;
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

    inline static void ShowCameraWindow(bool& showing)
    {
        ImGui::Begin("Camera", &showing);

        Cuscuz::OrthoCameraController& camera = Cuscuz::Engine::Get().CC_RendererSystem->GetCameraController();
        camera.OnImGuiRender();
        
        ImGui::End();
    }
}
