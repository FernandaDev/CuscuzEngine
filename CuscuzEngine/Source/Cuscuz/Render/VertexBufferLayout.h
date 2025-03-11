#pragma once
#include "..\Core\Core.h"
#include "GL/glew.h"

struct VertexBufferElement
{
    uint32_t Type;
    uint32_t Count;
    uint8_t Normalized;

    static uint32_t GetSizeOfType(uint32_t type)
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
    uint32_t m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    uint32_t GetStride() const { return m_Stride; }
    const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

    template<typename T>
    void Push(uint32_t count)
    {
        LOG_ERROR("Error");
    }

    template<>
    void Push<float>(uint32_t count)
    {
        m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<uint32_t>(uint32_t count)
    {
        m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<uint8_t>(uint32_t count)
    {
        m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
};
