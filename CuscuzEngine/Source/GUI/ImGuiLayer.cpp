#include "pch.h"
#include "EventSystem.h"
#include "imgui.h"
#include "Input.h"
#include "KeyCodes.h"
#include "GUI/imgui_impl_sdl.h"
#include "GUI/imgui_impl_sdlrenderer.h"
#include "Core/EngineApplication.h"
#include "Utils/Log.h"
#include "../Core/CC_Game.h"
#include "Components/SpriteComponent.h"
#include "Events/EventHandler.h"
#include "World/World.h"
#include "ImGuiLayer.h"

ImGuiLayer::ImGuiLayer(const Window& Window, SDL_Renderer* Renderer) :
Layer("ImGui Layer"), m_ShowMainWindow(true)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(Window.GetWindow(), Renderer);
    ImGui_ImplSDLRenderer_Init(Renderer);
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    UNSUBSCRIBE_KEY_EVENT(this, ImGuiLayer::ToggleMainWindow);
}

void ImGuiLayer::OnAttach()
{
    Layer::OnAttach();
    
    m_ShowMainWindow = true;
    EngineApplication::Get().CC_EventSystem->GetSDLEventDelegate()
                            .Add(this, &ImGuiLayer::OnSDLEvent);

    SUBSCRIBE_KEY_EVENT(CC_KeyEventType::Down, this, ImGuiLayer::ToggleMainWindow);
}

void ImGuiLayer::OnUpdate()
{
    Layer::OnUpdate();

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    if(m_ShowMainWindow)
        ShowMainWindow();

    Render();
}

void ImGuiLayer::ToggleMainWindow(const CC_Event<CC_KeyEventType>& Event)
{
    const auto keyDown = Event.ToType<CC_KeyDownEvent>();

    if(keyDown.GetKeyCode() == Tab)
        m_ShowMainWindow = !m_ShowMainWindow;
}

void ImGuiLayer::Render()
{
    const ImGuiIO io = ImGui::GetIO();
    ImGui::Render();
    SDL_RenderSetScale(EngineApplication::Get().CC_RendererSystem->GetRenderer(),
                        io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnSDLEvent(const SDL_Event& Event)
{
    ImGui_ImplSDL2_ProcessEvent(&Event);
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

void ImGuiLayer::ActorCreation(CC_Game* Game, bool Showing) const
{
}

void ImGuiLayer::ShowAllActors(CC_Game* Game, bool Showing) const
{
}

void ImGuiLayer::ShowActor(Actor* TheActor, int Index) const
{
}
