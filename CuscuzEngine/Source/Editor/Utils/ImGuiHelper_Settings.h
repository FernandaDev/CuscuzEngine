#pragma once
#include "Core/Time.h"
#include "Core/Window.h"
#include "Render/Renderer2D.h"

namespace ImGuiHelper
{
    static void ShowTimeOverlay(bool& showing)
    {
        static int location = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
                                        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                                        ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

        constexpr float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        const ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        const ImVec2 window_pos = {work_pos.x + PAD, work_pos.y + PAD};

        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, { 0.0f , 0.0f });
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

        if (ImGui::Begin("Time Stats", &showing, window_flags))
        {
            ImGui::Text("FPS: %i", Time::Get().GetFPS());
            ImGui::Text("Delta Time: %.4f seconds", static_cast<float>(Time::Get().DeltaTime()));
        }
        ImGui::End();
    }
    
    static void ShowTimeStatsWindow(bool& showing, bool& showTimeStats)
    {
        ImGui::Begin("Time Stats", &showing);
        
        ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Time");

        ImGui::Separator();

        ImGui::Checkbox("Show FPS", &showTimeStats);


        auto vSync = CC_Engine::Get().CC_Window->GetVSync();
        ImGui::Checkbox("VSync", &vSync);
        CC_Engine::Get().CC_Window->SetVSync(vSync);
        
        ImGui::End();
    }

    static void ShowRendererStatsWindow(bool& showing)
    {
        ImGui::Begin("Renderer Stats", &showing);
        
        ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Renderer 2D Statistics:");
        ImGui::Separator();

        const auto stats = Renderer2D::GetStats();
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::End();
    }
};