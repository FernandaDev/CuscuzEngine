﻿#include "pch.h"
#include "Renderer2D.h"

#include "Buffer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    glm::vec4 Color;
};

struct Renderer2DData
{
    const uint32_t MaxQuadsPerDraw = 10000;
    const uint32_t MaxVerticesPerDraw = MaxQuadsPerDraw * 4;
    const uint32_t MaxIndicesPerDraw = MaxQuadsPerDraw * 6;
    
    uint32_t QuadIndexCount = 0;

    CC_AssetRef<VertexArray> QuadVertexArray;
    CC_AssetRef<VertexBuffer> QuadVertexBuffer;
    CC_AssetRef<Shader> SpriteShader;
    CC_AssetRef<Texture2D> DefaultQuadTexture;

    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    s_Data.QuadVertexArray = VertexArray::Create();
    
    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVerticesPerDraw * sizeof(QuadVertex));
    s_Data.QuadVertexBuffer->SetLayout(
    {
        { ShaderDataType::Float3, "inPosition" },
        { ShaderDataType::Float2, "inTexCoord" },
        { ShaderDataType::Float4, "inColor" }
    });
    s_Data.QuadVertexArray->AddBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVerticesPerDraw];

    auto* quadIndices = new uint32_t[s_Data.MaxIndicesPerDraw];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_Data.MaxIndicesPerDraw; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }
    
    const CC_AssetRef<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndicesPerDraw);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
    delete[] quadIndices;

    s_Data.DefaultQuadTexture = Texture2D::Create(1, 1);
    uint32_t defaultTextureData = 0xffffffff;
    s_Data.DefaultQuadTexture->SetData(&defaultTextureData, sizeof(uint32_t));
    
    s_Data.SpriteShader = Shader::Create("SpriteBatch","Assets/Shaders/SpriteBatch.glsl");
    //s_Data.SpriteShader->SetUniformI("u_Texture", 0);
}

void Renderer2D::Shutdown()
{
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data.SpriteShader->Bind();
    s_Data.SpriteShader->SetUniformM4("u_ViewProjection", camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
}

void Renderer2D::EndScene()
{
    const uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
        
    Flush();   
}

void Renderer2D::Flush()
{
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
{
    DrawQuad({position.x, position.y, 0.0f}, scale, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
{
    s_Data.QuadVertexBufferPtr->Position = position;
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = { position.x + scale.x, position.y, 0.0f };
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = { position.x + scale.x, position.y + scale.y, 0.0f };
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + scale.y, 0.0f };
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
    /*s_Data.SpriteShader->Bind();
    s_Data.SpriteShader->SetUniformF4("u_Color", color);

    s_Data.QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
}

void Renderer2D::DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color, const CC_AssetRef<Texture2D>& texture)
{
    s_Data.SpriteShader->Bind();

    s_Data.SpriteShader->SetUniformM4("u_WorldTransform", worldTransform);
    s_Data.SpriteShader->SetUniformF4("u_Color", color);

    if(texture != nullptr)
        texture->Bind();
    else
        s_Data.DefaultQuadTexture->Bind();

    s_Data.QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
}