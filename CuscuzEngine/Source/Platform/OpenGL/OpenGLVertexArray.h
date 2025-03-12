#pragma once

#include "Cuscuz/Render/Buffer.h"
#include "Cuscuz/Render/VertexArray.h"

namespace Cuscuz
{
    class OpenGLVertexArray : public VertexArray
    {
        uint32_t m_RendererID;

        std::vector<CC_AssetRef<VertexBuffer>> m_VertexBuffers;
        CC_AssetRef<IndexBuffer> m_IndexBuffer;
    
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void AddBuffer(const CC_AssetRef<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const CC_AssetRef<IndexBuffer>& indexBuffer) override;
    
        void Bind() const override;
        void Unbind() const override;

        const std::vector<CC_AssetRef<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
        const CC_AssetRef<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
    };
}