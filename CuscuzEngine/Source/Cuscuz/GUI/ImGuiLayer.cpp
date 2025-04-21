#include "pch.h"

#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include "ImGuizmo.h"

#include "ImGuiLayer.h"
#include "Cuscuz/Core/EventSystem.h"
#include "Cuscuz/Core/Input.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Utils/Log.h"
#include "Cuscuz/Events/SDLEvent.h"
#include "Cuscuz/Core/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Cuscuz
{
    
    ImGuiLayer::ImGuiLayer(const Window& window) :
    Layer("ImGui Layer"), m_ShowDemoWindow(false)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
    
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.Fonts->AddFontFromFileTTF("Assets/Fonts/Kanit/Kanit-Light.ttf", 20.f);
        io.Fonts->AddFontFromFileTTF("Assets/Fonts/Kanit/Kanit-SemiBold.ttf", 20.f);
        
        io.FontDefault = io.Fonts->Fonts[0];

        GraphicsContext* context = window.GetContext();
        const auto openGlContext = (OpenGLContext*)context;
    
        ImGui_ImplSDL2_InitForOpenGL(window.GetSDLWindow(), openGlContext->GetContext());
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

        SetDarkThemeColors();
    }

    void ImGuiLayer::OnEvent(CuscuzEvent& event)
    {
        Layer::OnEvent(event);
    
        EventSingleDispatcher eventDispatcher(event);
        eventDispatcher.Dispatch<CC_SDLEvent>(BIND_FUNCTION(this, ImGuiLayer::OnSDLEvent));

        if(m_BlockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    bool ImGuiLayer::OnSDLEvent(const CC_SDLEvent& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event.GetSDLEvent());
        return false;
    }
    
    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }
    
    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        const Engine& engine = Engine::Get();
        io.DisplaySize = ImVec2(engine.CC_Window->GetWidth(), engine.CC_Window->GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
    }

    void ImGuiLayer::SetDarkThemeColors()  
    {  
        auto& colors = ImGui::GetStyle().Colors;  
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.141f, 0.125f, 0.004f, 1.0f};  
  
        //Headers  
        colors[ImGuiCol_Header] = ImVec4{ 0.212f, 0.208f, 0.196f, 1.0f};  
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.31f, 0.31f, 0.302f, 1.0f};  
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.162f, 0.1605f, 0.01f, 1.0f};  
  
        //Buttons  
        colors[ImGuiCol_Button] = ImVec4{ 0.212f, 0.208f, 0.196f, 1.0f};  
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.31f, 0.31f, 0.302f, 1.0f};  
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.162f, 0.1605f, 0.01f, 1.0f};  
  
        //Frame BG  
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.0f, 1.0f};  
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.0f, 1.0f};  
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.165f, 0.165f, 0.f, 1.0f};  
  
        //Tabs  
        colors[ImGuiCol_Tab] = ImVec4{ 0.21f, 0.22f, 0.176f, 1.0f};  
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.58f, 0.55f, 0.176f, 1.0f};  
        colors[ImGuiCol_TabActive] = ImVec4{ 0.48f, 0.45f, 0.15f, 1.0f};  
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.175f, 0.175f, 0.0f, 1.0f};  
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.25f, 0.25f, 0.f, 1.0f};  
  
        //Titles  
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.11f, 0.12f, 0.01f, 1.0f};  
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.11f, 0.12f, 0.01f, 1.0f};  
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.11f, 0.12f, 0.01f, 1.0f};  
  
        //Docking  
        colors[ImGuiCol_DockingPreview] = ImVec4{ 0.02f, 0.02f, 0.f, 1.0f};  
    }
}