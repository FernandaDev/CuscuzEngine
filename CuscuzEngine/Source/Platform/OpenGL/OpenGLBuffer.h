#pragma once
#include "Render/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
    uint32_t m_RendererID;
    
public:
    OpenGLVertexBuffer(const void* data, uint32_t size);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
};

class OpenGLIndexBuffer : public IndexBuffer
{
    uint32_t m_RendererID;
    uint32_t m_Count;
    
public:
    OpenGLIndexBuffer(const uint32_t* data, uint32_t count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    uint32_t GetCount() const { return m_Count; }
};
