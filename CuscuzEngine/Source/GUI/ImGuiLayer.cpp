#include "pch.h"
#include "EventSystem.h"
#include "imgui.h"
#include "Input.h"
#include "GUI/imgui_impl_sdl.h"
#include "GUI/imgui_impl_sdlrenderer.h"
#include "Core/EngineApplication.h"
#include "Utils/Log.h"
#include "../Core/CC_Game.h"
#include "Components/SpriteComponent.h"
#include "World/World.h"
#include "ImGuiLayer.h"

#include "KeyCodes.h"
#include "Events/SDLEvent.h"

ImGuiLayer::ImGuiLayer(const Window& window, SDL_Renderer* renderer) :
Layer("ImGui Layer"), m_ShowMainWindow(true)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.GetWindow(), renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnAttach()
{
    Layer::OnAttach();
    
    m_ShowMainWindow = true;
}

void ImGuiLayer::OnUpdate()
{
    Layer::OnUpdate();

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    if(m_ShowMainWindow)
        ShowMainWindow();

    const ImGuiIO io = ImGui::GetIO();
    ImGui::Render();
    SDL_RenderSetScale(EngineApplication::Get().CC_RendererSystem->GetRenderer(),
                        io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher sldEventDispatcher(event);
    sldEventDispatcher.Dispatch<CC_SDLEvent>(BIND_FUNCTION(this, ImGuiLayer::OnSDLEvent));
    
    CC_EventSingleDispatcher eventKeyDownDispatcher(event);
    eventKeyDownDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, ImGuiLayer::ToggleMainWindow));
}

bool ImGuiLayer::ToggleMainWindow(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() == CC_KeyCode::Tab)
        m_ShowMainWindow = !m_ShowMainWindow;

    return true;
}

bool ImGuiLayer::OnSDLEvent(const CC_SDLEvent& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event.GetSDLEvent());
    return true;
}

void ImGuiLayer::ShowMainWindow()
{
    ImGui::Begin("Game", &m_ShowMainWindow);

    if(ImGui::Button("Play"))
    {
        if(!EngineApplication::Get().m_Game->IsRunning())
            EngineApplication::Get().m_Game->StartGame();
    }

    ImGui::SameLine();
    
    if(ImGui::Button("Pause"))
    {
        EngineApplication::Get().m_Game->PauseGame();
    }
    
    ImGui::SameLine();
    
    if(ImGui::Button("Quit"))
    {
        EngineApplication::Get().m_Game->ShutdownGame();
    }
    
    ImGui::End();
}

void ImGuiLayer::ActorCreation(CC_Game* game, bool showing) const
{
}

void ImGuiLayer::ShowAllActors(CC_Game* game, bool showing) const
{
}

void ImGuiLayer::ShowActor(Actor* theActor, int index) const
{
}
