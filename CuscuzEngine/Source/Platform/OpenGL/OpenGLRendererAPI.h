#pragma once
#include "Render/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
    OpenGLRendererAPI();
    ~OpenGLRendererAPI() override = default;
    
    void Init() override;
    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    void SetClearColor(const glm::vec4& color) override;
    void Clear() override;
    void DrawIndexed(const CC_AssetRef<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
};
