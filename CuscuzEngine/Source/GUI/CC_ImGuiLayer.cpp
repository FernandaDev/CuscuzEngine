#include "pch.h"
#include "CC_ImGuiLayer.h"
#include "EventSystem.h"
#include "imgui.h"
#include "Input.h"
#include "KeyCodes.h"
#include "GUI/imgui_impl_sdl.h"
#include "GUI/imgui_impl_sdlrenderer.h"
#include "Core/EngineApplication.h"
#include "Utils/Log.h"
#include "../Core/CC_Game.h"
#include "Components/Animation2DComponent.h"
#include "Components/SpriteComponent.h"
#include "Events/EventHandler.h"
#include "World/Actor.h"
#include "World/World.h"

CC_ImGuiLayer::CC_ImGuiLayer(const Window& Window, SDL_Renderer* Renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(Window.GetWindow(), Renderer);
    ImGui_ImplSDLRenderer_Init(Renderer);
}

CC_ImGuiLayer::~CC_ImGuiLayer()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    UNSUBSCRIBE_KEY_EVENT(this, CC_ImGuiLayer::ToggleMainWindow);
}

void CC_ImGuiLayer::Init()
{
    m_ShowMainWindow = true;
    EngineApplication::Get().CC_EventSystem->GetSDLEventDelegate()
                            .Add(this, &CC_ImGuiLayer::OnSDLEvent);

    SUBSCRIBE_KEY_EVENT(CC_KeyEventType::Down, this, CC_ImGuiLayer::ToggleMainWindow);
}

void CC_ImGuiLayer::ToggleMainWindow(const CC_Event<CC_KeyEventType>& Event)
{
    const auto keyDown = Event.ToType<CC_KeyDownEvent>();

    if(keyDown.GetKeyCode() == Tab)
        m_ShowMainWindow = !m_ShowMainWindow;
}

void CC_ImGuiLayer::Update()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    if(m_ShowMainWindow)
        ShowMainWindow();
}

void CC_ImGuiLayer::Render()
{
    const ImGuiIO io = ImGui::GetIO();
    ImGui::Render();
    SDL_RenderSetScale(EngineApplication::Get().CC_RendererSystem->GetRenderer(),
                        io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void CC_ImGuiLayer::OnSDLEvent(const SDL_Event& Event)
{
    ImGui_ImplSDL2_ProcessEvent(&Event);
}

void CC_ImGuiLayer::ShowMainWindow()
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

void CC_ImGuiLayer::ActorCreation(CC_Game* Game, bool Showing) const
{
}

void CC_ImGuiLayer::ShowAllActors(CC_Game* Game, bool Showing) const
{
}

void CC_ImGuiLayer::ShowActor(Actor* TheActor, int Index) const
{
}
