#include "pch.h"
#include "Renderer2D.h"

#include "Buffer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

struct Renderer2DData
{
    CC_AssetRef<VertexArray> SpriteVertexArray;
    CC_AssetRef<Shader> SpriteShader;
    CC_AssetRef<Texture> DefaultSpriteTexture;
};

static Renderer2DData* s_Data;

void Renderer2D::Init()
{
    s_Data = new Renderer2DData();

    s_Data->DefaultSpriteTexture = Texture2D::Create(1, 1);
    uint32_t defaultTextureData = 0xffffffff;
    s_Data->DefaultSpriteTexture->SetData(&defaultTextureData, sizeof(uint32_t));
    
    s_Data->SpriteVertexArray = VertexArray::Create();
    
    constexpr float vertices[4 * 5] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // vertex 0 top left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // vertex 1 top right
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // vertex 2 bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // vertex 3 bottom left
    };
    
    constexpr uint32_t indices[6] = { 0, 1, 2, 2, 3, 0};
    
    const CC_AssetRef<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices,  4 * 5 * sizeof(float));
    const CC_AssetRef<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 6);

    const BufferLayout layout =
    {
        { ShaderDataType::Float3, "inPosition" },
        { ShaderDataType::Float2, "inTexCoord" }
    };
    
    vertexBuffer->SetLayout(layout);

    s_Data->SpriteVertexArray->AddBuffer(vertexBuffer);
    s_Data->SpriteVertexArray->SetIndexBuffer(indexBuffer);

    s_Data->SpriteShader = Shader::Create("Sprite","Assets/Shaders/Sprite.glsl");
    s_Data->SpriteShader->SetUniformI("u_Texture", 0);
}

void Renderer2D::Shutdown()
{
    delete s_Data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data->SpriteShader->Bind();
    s_Data->SpriteShader->SetUniformM4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Renderer2D::EndScene()
{
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
{
    DrawQuad({position.x, position.y, 0.0f}, scale, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
{
    s_Data->SpriteShader->Bind();
    s_Data->SpriteShader->SetUniformF4("u_Color", color);

    s_Data->SpriteVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->SpriteVertexArray);
}

void Renderer2D::DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color, const CC_AssetRef<Texture2D>& texture)
{
    s_Data->SpriteShader->Bind();

    s_Data->SpriteShader->SetUniformM4("u_WorldTransform", worldTransform);
    s_Data->SpriteShader->SetUniformF4("u_Color", color);

    if(texture != nullptr)
        texture->Bind();
    else
        s_Data->DefaultSpriteTexture->Bind();

    s_Data->SpriteVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->SpriteVertexArray);
}