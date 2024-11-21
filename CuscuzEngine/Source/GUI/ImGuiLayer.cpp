#include "pch.h"

#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>

#include "ImGuiLayer.h"
#include "Core/EventSystem.h"
#include "Core/Input.h"
#include "Core/CC_Engine.h"
#include "Core/KeyCodes.h"
#include "Utils/Log.h"
#include "Events/SDLEvent.h"
#include "Core/Window.h"
#include "GL/glew.h"

ImGuiLayer::ImGuiLayer(const Window& window) :
Layer("ImGui Layer"), m_ShowDemoWindow(false)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    ImGui_ImplSDL2_InitForOpenGL(window.GetWindow(), window.GetCurrentContext());
    ImGui_ImplOpenGL3_Init("#version 330");
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
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
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, ImGuiLayer::OnKeyDown));
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if(m_ShowDemoWindow)
        ImGui::ShowDemoWindow(&m_ShowDemoWindow);
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();
    
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


bool ImGuiLayer::OnSDLEvent(const CC_SDLEvent& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event.GetSDLEvent());
    return true;
}

bool ImGuiLayer::OnKeyDown(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() != CC_KeyCode::F8)
        return false;

    m_ShowDemoWindow = !m_ShowDemoWindow;
    
    return false;
}
