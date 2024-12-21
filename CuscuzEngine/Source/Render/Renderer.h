#pragma once
#include "Camera.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const CC_AssetRef<Shader>& shader, const CC_AssetRef<VertexArray>& vertexArray);

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};
