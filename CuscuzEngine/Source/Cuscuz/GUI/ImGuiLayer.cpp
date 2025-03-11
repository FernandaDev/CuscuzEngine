#include "pch.h"

#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

#include "ImGuiLayer.h"
#include "Cuscuz/Core/EventSystem.h"
#include "Cuscuz/Core/Input.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Core/KeyCodes.h"
#include "Cuscuz/Utils/Log.h"
#include "Cuscuz/Events/SDLEvent.h"
#include "Cuscuz/Core/Window.h"
#include "GL/glew.h"
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

        GraphicsContext* context = window.GetContext();
        const auto openGlContext = (OpenGLContext*)context;
    
        ImGui_ImplSDL2_InitForOpenGL(window.GetWindow(), openGlContext->GetContext());
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

    void ImGuiLayer::OnEvent(CuscuzEvent& event)
    {
        Layer::OnEvent(event);
    
        EventSingleDispatcher eventDispatcher(event);
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


    bool ImGuiLayer::OnSDLEvent(const CC_SDLEvent& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event.GetSDLEvent());
        return false;
    }

    bool ImGuiLayer::OnKeyDown(const CC_KeyDownEvent& event)
    {
        if(event.GetKeyCode() != CC_KeyCode::F8)
            return false;

        m_ShowDemoWindow = !m_ShowDemoWindow;
    
        return false;
    }
}