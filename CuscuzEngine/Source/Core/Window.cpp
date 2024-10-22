#include "pch.h"
#include "Window.h"

#include "Events/CC_EventDispatcher.h"
#include "Events/WindowEvents.h"
#include "Utils/Log.h"

#include "GL/glew.h"

Window::Window(int width, int height):
    m_Width{width}, m_Height{height}
{
}

Window::~Window()
{
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
}

void Window::Init(const char* name)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("SDL could not be initialized: %s", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    m_Window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_Width, m_Height,
                                SDL_WINDOW_OPENGL);

    if (!m_Window)
        LOG_ERROR("Could not create a window.");

    m_Context = SDL_GL_CreateContext(m_Window);

    SDL_GL_MakeCurrent(m_Window, m_Context);

    if (glewInit() != GLEW_OK)
        LOG_ERROR("Couldn't initialize glew.");
    else
        std::cout << "Glew has successfully initialized! Gl Version: " << glGetString(GL_VERSION) << std::endl;
}

void Window::OnEvent(CC_Event& event)
{
    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_WindowResizeEvent>(BIND_FUNCTION(this, Window::OnWindowResized));
}

bool Window::OnWindowResized(const CC_WindowResizeEvent& event)
{
    m_Height = event.GetHeight();
    m_Width = event.GetWidth();

    return true;
}
