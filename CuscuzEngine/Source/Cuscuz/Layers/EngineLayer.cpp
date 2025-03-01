#include "pch.h"

#include "EngineLayer.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Core/EventSystem.h"
#include "Cuscuz/Core/KeyCodes.h"
#include "Cuscuz/Core/RendererSystem.h"
#include "Cuscuz/Events/KeyEvents.h"
#include "Cuscuz/Core/PhysicsSystem.h"

#include <imgui.h>

namespace Cuscuz
{
    void EngineLayer::OnUpdate(float deltaTime) // TODO move all the main system to here!
    {
        Layer::OnUpdate(deltaTime);

        Engine::Get().CC_PhysicsSystem->OnUpdate();
        Engine::Get().CC_RendererSystem->OnUpdate(deltaTime);
    }

    void EngineLayer::OnEvent(CC_Event& event)
    {
        Engine::Get().CC_RendererSystem->OnEvent(event);
    
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
}
