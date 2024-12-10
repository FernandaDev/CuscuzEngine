#pragma once
#include "Render/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
    OpenGLRendererAPI();
    ~OpenGLRendererAPI() override = default;
    
    void SetClearColor(const glm::vec4& color) override;
    void Clear() override;
    void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    void EnableBlend() override;
};
