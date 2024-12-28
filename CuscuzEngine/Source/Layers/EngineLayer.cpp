#include "pch.h"
#include <imgui.h>

#include "EngineLayer.h"

#include "Core/CC_Engine.h"
#include "Core/EventSystem.h"
#include "Core/KeyCodes.h"
#include "Core/PhysicsSystem.h"
#include "Core/RendererSystem.h"
#include "Events/KeyEvents.h"

void EngineLayer::OnUpdate(float deltaTime) // TODO move all the main system to here!
{
    Layer::OnUpdate(deltaTime);

    CC_Engine::Get().CC_EventSystem->OnUpdate();
    CC_Engine::Get().CC_PhysicsSystem->OnUpdate();
    CC_Engine::Get().CC_RendererSystem->OnUpdate(deltaTime);
}

void EngineLayer::OnEvent(CC_Event& event)
{
    CC_Engine::Get().CC_RendererSystem->OnEvent(event);
    
    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, EngineLayer::TogglePlayWindow));
}

void EngineLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    //if(m_ShowPlayWindow)
      //  ShowPlayWindow();
}

bool EngineLayer::TogglePlayWindow(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() == CC_KeyCode::Tab)
        m_ShowPlayWindow = !m_ShowPlayWindow;

    return false;
}

void EngineLayer::ShowPlayWindow()
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