﻿#include "pch.h"
#include "EditorLayer.h"

#include "imgui.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Core/KeyCodes.h"
#include "Cuscuz/Events/KeyEvents.h"
#include "Utils/ImGuiHelper_ActorCreation.h"
#include "Utils/ImGuiHelper_Settings.h"
#include "Utils/ImGuiHelper_World.h"

namespace Cuscuz
{
    EditorLayer::EditorLayer() : m_ShowWorldWindow(true), m_ShowTimeStatsOverlay(true)
    {
        m_World = Engine::Get().CC_World.get();
    }

    void EditorLayer::OnImGuiRender()
    {
        if (m_ShowWorldWindow)
            ShowWorldWindow();

        if(m_ShowTimeStatsOverlay)
            ImGuiHelper::ShowTimeOverlay(m_ShowTimeStatsOverlay);
    }

    void EditorLayer::OnEvent(CC_Event& event)
    {
        Layer::OnEvent(event);

        CC_EventSingleDispatcher eventDispatcher(event);
        eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, EditorLayer::ToggleWindow));
    }

    bool EditorLayer::ToggleWindow(const CC_KeyDownEvent& event)
    {
        if (event.GetKeyCode() == CC_KeyCode::F1)
            m_ShowWorldWindow = !m_ShowWorldWindow;

        return false;
    }

    void EditorLayer::ShowWorldWindow()
    {
        ImGui::Begin("World", &m_ShowWorldWindow, ImGuiWindowFlags_MenuBar);

        static bool showActorCreation = false;
        static bool showCameraWindow = false;
        static bool showTimeStatsWindow = false;
        static bool showRendererStatsWindow = true;
    
        if (ImGui::BeginMenuBar())
        {
            if(ImGui::BeginMenu("Tools"))
            {
                ImGui::MenuItem("Create New Actor", NULL, &showActorCreation);

                ImGui::EndMenu();
            }
        
            if(ImGui::BeginMenu("Camera"))
            {
                ImGui::MenuItem("Settings", NULL, &showCameraWindow);
            
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Stats"))
            {
                ImGui::MenuItem("Time", NULL, &showTimeStatsWindow);
                ImGui::MenuItem("Renderer", NULL, &showRendererStatsWindow);
            
                ImGui::EndMenu();
            }
        
            ImGui::EndMenuBar();
        }
    
        if(showActorCreation)
            ImGuiHelper::ShowActorCreation(showActorCreation, m_World);

        if(showCameraWindow)
            ImGuiHelper::ShowCameraWindow(showCameraWindow);

        if(showTimeStatsWindow)
            ImGuiHelper::ShowTimeStatsWindow(showTimeStatsWindow, m_ShowTimeStatsOverlay);

        if(showRendererStatsWindow)
            ImGuiHelper::ShowRendererStatsWindow(showRendererStatsWindow);

        const bool showingActors = ImGui::CollapsingHeader("Hierarchy", ImGuiTreeNodeFlags_DefaultOpen);
        ImGuiHelper::ShowAllActors(showingActors, m_World);
    
        ImGui::End();
    }
}