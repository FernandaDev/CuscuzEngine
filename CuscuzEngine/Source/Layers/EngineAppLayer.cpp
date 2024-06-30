#include "pch.h"

#include "EngineAppLayer.h"

#include "EventSystem.h"
#include "imgui.h"
#include "KeyCodes.h"
#include "Core/Time.h"
#include "Core/CC_Game.h"
#include "RendererSystem.h"
#include "Events/KeyEvents.h"

class CC_KeyDownEvent;

EngineAppLayer::EngineAppLayer(EventSystem* eventSystem, RendererSystem* renderer, CC_Game* game) :
Layer("Engine App Layer"), m_EventSystem(eventSystem), m_RendererSystem(renderer), m_Game(game),
m_ShowPlayWindow(true)
{}

void EngineAppLayer::OnUpdate()
{
    Layer::OnUpdate();

    m_EventSystem->Update();
    
    m_RendererSystem->Update();
    
    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}

void EngineAppLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if(m_ShowPlayWindow)
        ShowPlayWindow();
}

void EngineAppLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, EngineAppLayer::ToggleMainWindow));
}

bool EngineAppLayer::ToggleMainWindow(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() == CC_KeyCode::Tab)
        m_ShowPlayWindow = !m_ShowPlayWindow;

    return false;
}

void EngineAppLayer::ShowPlayWindow()
{
    ImGui::Begin("Game", &m_ShowPlayWindow);

    if(ImGui::Button("Play"))
    {
        if(!m_Game->IsRunning())
            m_Game->StartGame();
    }

    ImGui::SameLine();
    
    if(ImGui::Button("Pause"))
    {
        m_Game->PauseGame();
    }
    
    ImGui::SameLine();
    
    if(ImGui::Button("Quit"))
    {
        m_Game->ShutdownGame();
    }
    
    ImGui::End();
}