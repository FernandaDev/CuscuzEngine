#include "pch.h"
#include "EditorLayer.h"

#include "imgui.h"
#include "Core/CC_Engine.h"
#include "Core/KeyCodes.h"
#include "Events/KeyEvents.h"
#include "Utils/ImGuiHelper_ActorCreation.h"
#include "Utils/ImGuiHelper_World.h"

EditorLayer::EditorLayer() : m_ShowWorldWindow(true), m_ShowActorCreation(false)
{
    m_World = CC_Engine::Get().CC_World.get();
}

void EditorLayer::OnImGuiRender()
{
    if (m_ShowWorldWindow)
        ShowWorldWindow();
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

    if (ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Create New Actor", NULL, &m_ShowActorCreation);

            ImGui::EndMenu();
        }
        
        ImGui::EndMenuBar();
    }
    
    if(m_ShowActorCreation)
        ImGuiHelper::ShowActorCreation(m_ShowActorCreation, m_World);

    const bool showingActors = ImGui::CollapsingHeader("Hierarchy", ImGuiTreeNodeFlags_DefaultOpen);
    ImGuiHelper::ShowAllActors(showingActors, m_World);
    
    ImGui::End();
}
