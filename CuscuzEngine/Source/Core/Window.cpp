#include "pch.h"
#include "Window.h"

#include "Events/CC_EventDispatcher.h"
#include "Events/WindowEvents.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Render/Renderer.h"
#include "Utils/Log.h"


Window::Window(int width, int height):
    m_Width{width}, m_Height{height}, m_VSync(true), m_Minimized(false)
{}

Window::~Window()
{
    SDL_DestroyWindow(m_Window);
}

void Window::Init(const char* name)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("SDL could not be initialized: %s", SDL_GetError());
        return;
    }

    m_Window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_Width, m_Height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!m_Window)
        LOG_ERROR("Could not create a window.");

    m_Context = std::make_unique<OpenGLContext>(m_Window);
    m_Context->Init();
}

void Window::OnEvent(CC_Event& event)
{
    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_WindowResizeEvent>(BIND_FUNCTION(this, Window::OnWindowResized));
    eventDispatcher.Dispatch<CC_WindowMinimizedEvent>(BIND_FUNCTION(this, Window::OnWindowMinimized));
    eventDispatcher.Dispatch<CC_WindowRestoredFocusEvent>(BIND_FUNCTION(this, Window::OnWindowRestoredFocus));
}

void Window::Render()
{
    m_Context->Render();
}

void Window::SetVSync(bool enable)
{
    if(enable)
        SDL_GL_SetSwapInterval(1);
    else
        SDL_GL_SetSwapInterval(0);

    m_VSync = enable;
}

bool Window::OnWindowResized(const CC_WindowResizeEvent& event)
{
    m_Height = event.GetHeight();
    m_Width = event.GetWidth();

    Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
    
    return false;
}

bool Window::OnWindowMinimized(const CC_WindowMinimizedEvent& event)
{
    m_Minimized = true;
    LOG_INFO("The window has minimized!");
    
    return false;
}

bool Window::OnWindowRestoredFocus(const CC_WindowRestoredFocusEvent& event)
{
    m_Minimized = false;
    LOG_INFO("The window has restored focus!");
    
    return false;
}
