#include "pch.h"
#include "Renderer2D.h"

#include "Buffer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Components/TransformComponent.h"

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
    glm::vec2 TilingOffset;
};

struct Renderer2DData
{
    const uint32_t MaxQuadsPerDraw = 10000;
    const uint32_t MaxVerticesPerDraw = MaxQuadsPerDraw * 4;
    const uint32_t MaxIndicesPerDraw = MaxQuadsPerDraw * 6;
    static constexpr int32_t MaxTextureSlotsPerDraw = 32;
    
    uint32_t QuadIndexCount = 0;

    CC_AssetRef<VertexArray> QuadVertexArray;
    CC_AssetRef<VertexBuffer> QuadVertexBuffer;
    CC_AssetRef<Shader> SpriteShader;
    CC_AssetRef<Texture2D> DefaultQuadTexture;

    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;

    std::array<CC_AssetRef<Texture2D>, MaxTextureSlotsPerDraw> TextureSlots;
    uint32_t TextureSlotIndex = 1;

    glm::vec4 QuadVertexPositions[4];
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    s_Data.QuadVertexArray = VertexArray::Create();
    
    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVerticesPerDraw * sizeof(QuadVertex));
    s_Data.QuadVertexBuffer->SetLayout(
    {
        { ShaderDataType::Float3, "inPosition" },
        { ShaderDataType::Float4, "inColor" },
        { ShaderDataType::Float2, "inTexCoord" },
        { ShaderDataType::Float, "inTexIndex" },
        { ShaderDataType::Float2, "inTilingOffset" },
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
    s_Data.SpriteShader->Bind();
    
    int32_t samplers[Renderer2DData::MaxTextureSlotsPerDraw];
    for (int32_t i = 0; i < Renderer2DData::MaxTextureSlotsPerDraw; i++)
        samplers[i] = i;
    
    s_Data.SpriteShader->SetIntArray("u_Textures", samplers, Renderer2DData::MaxTextureSlotsPerDraw);

    s_Data.TextureSlots[0] = s_Data.DefaultQuadTexture;

    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
}

void Renderer2D::Shutdown()
{
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data.SpriteShader->Bind();
    s_Data.SpriteShader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
    s_Data.TextureSlotIndex = 1;
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
    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; ++i)
        s_Data.TextureSlots[i]->Bind(i);
    
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::DrawQuad(const TransformComponent& transform, const glm::vec4& color)
{
    const auto worldTransform = transform.GetWorldTransform(); 
    
    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
    s_Data.QuadVertexBufferPtr->TilingOffset = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
    s_Data.QuadVertexBufferPtr->TilingOffset = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
    s_Data.QuadVertexBufferPtr->TilingOffset = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
    s_Data.QuadVertexBufferPtr->TilingOffset = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawQuad(const TransformComponent& transform, const glm::vec4& color, const CC_AssetRef<Texture2D>& texture, const glm::vec2& tilingOffset)
{
    float textureIndex = 0.0f;

    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i)
    {
        if(*s_Data.TextureSlots[i] == *texture)
        {
            textureIndex = static_cast<float>(i);
            break;
        }
    }
    
    if(textureIndex == 0.0f)
    {
        textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
        s_Data.TextureSlotIndex++;
    }

    const auto worldTransform = transform.GetWorldTransform(); 
    
    s_Data.QuadVertexBufferPtr->Position = worldTransform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingOffset = tilingOffset;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingOffset = tilingOffset;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = worldTransform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingOffset = tilingOffset;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position =  worldTransform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingOffset = tilingOffset;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}