#include "pch.h"
#include "VertexArray.h"
#include "GL/glew.h"
#include "Render/Buffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
    Bind(); // bind the vertex array
    vertexBuffer.Bind(); // binds the vertex buffer to setup it's layout

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i); 
        glVertexAttribPointer(i, element.Count, element.Type,
            element.Normalized, layout.GetStride(), (const void*)offset);
        offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
