#include "pch.h"
#include "OpenGLContext.h"
#include "GL/glew.h"

OpenGLContext::OpenGLContext(SDL_Window* window) : m_Window( window)
{}

OpenGLContext::~OpenGLContext()
{
    SDL_GL_DeleteContext(m_Context);
}

void OpenGLContext::Init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    m_Context = SDL_GL_CreateContext(m_Window);
    SDL_GL_MakeCurrent(m_Window, m_Context);
    
    if (glewInit() != GLEW_OK)
        LOG_ERROR("Couldn't initialize glew.");

    LOG_INFO("OpenGl Info:");
    LOG_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    LOG_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    LOG_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void OpenGLContext::Render()
{
    SDL_GL_SwapWindow(m_Window);
}
