#include "pch.h"

#include "OpenGLVertexArray.h"
#include "GL/glew.h"

namespace Cuscuz
{
    static uint32_t ShaderDataTypeToOpenGLType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: return GL_FLOAT;
    
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4: return GL_INT;

        case ShaderDataType::Bool: return GL_BOOL;

        case ShaderDataType::None:
        default:
            {
                CC_ASSERT(false, "Invalid shader type!")
                return 0;
            }
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::AddBuffer(const CC_AssetRef<VertexBuffer>& vertexBuffer)
    {
        CC_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!")

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
    
        auto layout = vertexBuffer->GetLayout();

        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index); 
            glVertexAttribPointer(index, element.GetElementCount(),
                ShaderDataTypeToOpenGLType(element.Type),
                element.Normalized? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);

            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const CC_AssetRef<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
    
        m_IndexBuffer = indexBuffer;
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}