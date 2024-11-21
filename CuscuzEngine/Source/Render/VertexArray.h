#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
    unsigned int m_RendererID;
    
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
    
    void Bind() const;
    void Unbind() const;
};
