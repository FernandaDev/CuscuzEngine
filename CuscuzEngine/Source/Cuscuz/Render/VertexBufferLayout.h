#pragma once
#include "..\Core\Core.h"
#include "GL/glew.h"

struct VertexBufferElement
{
    unsigned int Type;
    unsigned int Count;
    unsigned char Normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                LOG_ERROR("Error");
                return 0;
        }
    }
};

class VertexBufferLayout
{
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    unsigned int GetStride() const { return m_Stride; }
    const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

    template<typename T>
    void Push(unsigned int count)
    {
        LOG_ERROR("Error");
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
};
