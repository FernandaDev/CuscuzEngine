﻿#include "pch.h"

#include "CC_MainLayer.h"
#include "EventSystem.h"
#include "imgui.h"
#include "KeyCodes.h"
#include "Core/Time.h"
#include "Core/CC_Game.h"
#include "RendererSystem.h"
#include "CC_Engine.h"
#include "Events/KeyEvents.h"

CC_MainLayer::CC_MainLayer(const std::shared_ptr<CC_Game>& game):
m_Game(game), m_ShowPlayWindow(true) {}

void CC_MainLayer::OnUpdate()
{
    Layer::OnUpdate();

    CC_Engine::Get().CC_EventSystem->Update();
    CC_Engine::Get().CC_RendererSystem->Update();
    
    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}

void CC_MainLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if(m_ShowPlayWindow)
        ShowPlayWindow();
}

void CC_MainLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, CC_MainLayer::TogglePlayWindow));
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