﻿#include "pch.h"
#include "OpenGLRendererAPI.h"

#include "GL/glew.h"

OpenGLRendererAPI::OpenGLRendererAPI()
{
    s_CurrentAPI = API::OpenGL;
}

void OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Cuscuz::CC_AssetRef<Cuscuz::VertexArray>& vertexArray, uint32_t indexCount)
{
    const auto count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}