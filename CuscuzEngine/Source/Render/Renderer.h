#pragma once

enum class RendererAPI
{
    None = 0,
    OpenGL = 1
};

class Renderer
{
    static RendererAPI s_CurrentAPI;

public:
    static RendererAPI GetAPI() { return s_CurrentAPI; }
    static void SetAPI(RendererAPI type) { s_CurrentAPI = type; }
};
