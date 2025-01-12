#pragma once
#include "glm.hpp"
#include "VertexArray.h"

class RendererAPI
{
public:
    virtual ~RendererAPI() = default;

    enum class API
    {
        None = 0,
        OpenGL = 1
    };

protected:
    static API s_CurrentAPI;

public:
    static API GetAPI() { return s_CurrentAPI; }

    virtual void Init() = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;
    virtual void DrawIndexed(const CC_AssetRef<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
};
