#pragma once

#include "RendererAPI.h"

class RenderCommand
{
public:
    static void SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    static void Clear()
    {
        s_RendererAPI->Clear();
    }

    static void EnableBlend()
    {
        s_RendererAPI->EnableBlend();
    }
    
    static void DrawIndexed(const CC_AssetRef<VertexArray>& vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }
    
private:
    static RendererAPI* s_RendererAPI;
};
