#pragma once

#include "Cuscuz/Render/Buffer.h"
#include "Cuscuz/Render/VertexArray.h"

class OpenGLVertexArray : public Cuscuz::VertexArray
{
    uint32_t m_RendererID;

    std::vector<Cuscuz::CC_AssetRef<Cuscuz::VertexBuffer>> m_VertexBuffers;
    Cuscuz::CC_AssetRef<Cuscuz::IndexBuffer> m_IndexBuffer;
    
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void AddBuffer(const Cuscuz::CC_AssetRef<Cuscuz::VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const Cuscuz::CC_AssetRef<Cuscuz::IndexBuffer>& indexBuffer) override;
    
    void Bind() const override;
    void Unbind() const override;

    const std::vector<Cuscuz::CC_AssetRef<Cuscuz::VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
    const Cuscuz::CC_AssetRef<Cuscuz::IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
};
