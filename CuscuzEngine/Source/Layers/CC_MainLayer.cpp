#include "pch.h"
#include <imgui.h>

#include "CC_MainLayer.h"

#include "Core/CC_Engine.h"
#include "Core/EventSystem.h"
#include "Core/KeyCodes.h"
#include "Core/RendererSystem.h"
#include "Events/KeyEvents.h"

void CC_MainLayer::OnAttach()
{
    Layer::OnAttach();

}

void CC_MainLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);

    CC_Engine::Get().CC_EventSystem->Update();
    CC_Engine::Get().CC_RendererSystem->Update();
}

void CC_MainLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, CC_MainLayer::TogglePlayWindow));
}

void CC_MainLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if(m_ShowPlayWindow)
        ShowPlayWindow();
}

bool CC_MainLayer::TogglePlayWindow(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() == CC_KeyCode::Tab)
        m_ShowPlayWindow = !m_ShowPlayWindow;

    return false;
}

void CC_MainLayer::ShowPlayWindow()
{
    ImGui::Begin("Game", &m_ShowPlayWindow);
    
    if(ImGui::Button("Play"))
    {
        if(m_GameState != GameState::Running)
            LOG_INFO("Game is playing...");
    }
    
    ImGui::SameLine();
    
    if(ImGui::Button("Pause"))
    {
        m_GameState = GameState::Paused;
        LOG_INFO("Game is paused...");
    }
    
    ImGui::SameLine();
    
    if(ImGui::Button("Quit"))
    {
        LOG_INFO("Game has shutdown...");
        m_GameState = GameState::Off;
    }
    
    ImGui::End();
}