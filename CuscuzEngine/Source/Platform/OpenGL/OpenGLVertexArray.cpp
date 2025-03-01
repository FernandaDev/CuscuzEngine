#include "pch.h"

#include "OpenGLVertexArray.h"
#include "GL/glew.h"

static uint32_t ShaderDataTypeToOpenGLType(Cuscuz::ShaderDataType type)
{
    switch (type)
    {
        case Cuscuz::ShaderDataType::Float:
        case Cuscuz::ShaderDataType::Float2:
        case Cuscuz::ShaderDataType::Float3:
        case Cuscuz::ShaderDataType::Float4:
        case Cuscuz::ShaderDataType::Mat3:
        case Cuscuz::ShaderDataType::Mat4: return GL_FLOAT;
    
        case Cuscuz::ShaderDataType::Int:
        case Cuscuz::ShaderDataType::Int2:
        case Cuscuz::ShaderDataType::Int3:
        case Cuscuz::ShaderDataType::Int4: return GL_INT;

        case Cuscuz::ShaderDataType::Bool: return GL_BOOL;

        case Cuscuz::ShaderDataType::None:
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

void OpenGLVertexArray::AddBuffer(const Cuscuz::CC_AssetRef<Cuscuz::VertexBuffer>& vertexBuffer)
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

void OpenGLVertexArray::SetIndexBuffer(const Cuscuz::CC_AssetRef<Cuscuz::IndexBuffer>& indexBuffer)
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
