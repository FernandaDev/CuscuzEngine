#pragma once
#include "Cuscuz/Render/Buffer.h"

class OpenGLVertexBuffer : public Cuscuz::VertexBuffer
{
    uint32_t m_RendererID = 0;
    Cuscuz::BufferLayout m_Layout = {};
    
public:
    OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(const void* data, uint32_t size);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
    
    void SetData(const void* data, uint32_t size) override;

    const Cuscuz::BufferLayout& GetLayout() const override { return m_Layout;}
    void SetLayout(const Cuscuz::BufferLayout& layout) override { m_Layout = layout; }
};

class OpenGLIndexBuffer : public Cuscuz::IndexBuffer
{
    uint32_t m_RendererID;
    uint32_t m_Count;
    
public:
    OpenGLIndexBuffer(const uint32_t* data, uint32_t count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    uint32_t GetCount() const override { return m_Count; }
};
