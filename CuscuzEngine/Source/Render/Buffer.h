#pragma once

class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer* Create(const void* data, uint32_t size);
};


class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static IndexBuffer* Create(const uint32_t* data, uint32_t count);
};