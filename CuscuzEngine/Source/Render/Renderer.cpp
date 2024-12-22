#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

Renderer::SceneData* Renderer::s_SceneData = new SceneData;

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const CC_AssetRef<Shader>& shader, const CC_AssetRef<VertexArray>& vertexArray)
{
    shader->Bind();
    shader->SetUniformM4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
