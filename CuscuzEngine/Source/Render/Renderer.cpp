#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

Renderer::SceneData* Renderer::s_SceneData = new SceneData;

void Renderer::BeginScene(OrthographicCamera& camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
    shader->Bind();
    shader->SetUniformM4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
