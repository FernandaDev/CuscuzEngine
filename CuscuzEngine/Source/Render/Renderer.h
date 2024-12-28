#pragma once
#include "Camera.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
    static void Init();
    static void OnWindowResize(uint32_t width, uint32_t height);
    static void BeginScene(const OrthographicCamera& camera);
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
