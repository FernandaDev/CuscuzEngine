﻿#pragma once
#include <SDL_video.h>

#include "Render/GraphicsContext.h"

class OpenGLContext : public GraphicsContext
{
    SDL_Window* m_Window{};
    SDL_GLContext m_Context {};
    
public:
    OpenGLContext(SDL_Window* window);
    ~OpenGLContext();

    SDL_GLContext GetContext() const { return m_Context; }
    
    void Init() override;
    void Render() override;
};