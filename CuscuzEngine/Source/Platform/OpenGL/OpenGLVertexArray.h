#pragma once

#include "Render/Buffer.h"
#include "Render/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
    uint32_t m_RendererID;

    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void AddBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
    
    void Bind() const override;
    void Unbind() const override;

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
};
