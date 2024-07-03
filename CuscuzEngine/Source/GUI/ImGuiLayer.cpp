#include "pch.h"

#include <backends/imgui_impl_sdlrenderer.h>
#include <backends/imgui_impl_sdl.h>

#include "ImGuiLayer.h"
#include "EventSystem.h"
#include "imgui.h"
#include "Input.h"
#include "Core/EngineApplication.h"
#include "Utils/Log.h"
#include "Components/SpriteComponent.h"
#include "Events/SDLEvent.h"

ImGuiLayer::ImGuiLayer(const Window& window, SDL_Renderer* renderer) :
Layer("ImGui Layer"), m_ShowMainWindow(true)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplSDL2_InitForSDLRenderer(window.GetWindow(), renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
    
    m_ShowMainWindow = true;
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
}

void ImGuiLayer::OnDetach()
{
    Layer::OnDetach();
}

void ImGuiLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_SDLEvent>(BIND_FUNCTION(this, ImGuiLayer::OnSDLEvent));
}

void ImGuiLayer::Begin()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();
    SDL_RenderSetScale(EngineApplication::Get().CC_RendererSystem->GetRenderer(),
                        io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}


bool ImGuiLayer::OnSDLEvent(const CC_SDLEvent& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event.GetSDLEvent());
    return true;
}